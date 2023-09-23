#include "container.h"
#include "bank_server.h"

void BankServer::print_account_status(const SimpleRequest& req, ShowAccountReply& reply) {
	int id = req.id();
	int r = where_id(id);
	AccountMsg *acc_obj = new AccountMsg();
	acc_obj->set_id(m_users[r].m_id);
	acc_obj->set_name(m_users[r].m_name);
	acc_obj->set_type(m_users[r].m_type);
	acc_obj->set_demand_balance(m_users[r].m_demand_balance);
	acc_obj->set_password(m_users[r].m_password);
	acc_obj->set_locked(m_users[r].m_locked);
	acc_obj->set_loan(m_users[r].m_loan);
	acc_obj->set_auto_payment(m_users[r].m_auto_payment);
	// converts balances
	for (auto& balance : m_users[r].m_saving_balance) {
		std::ostringstream oss;
		oss << std::put_time(&balance.second, "%Y-%m-%d %H:%M:%S");
		auto tm_str = oss.str();
		auto type = balance.first.first;
		auto amount = balance.first.second;
		bank::SaveBalance *balc = acc_obj->add_balances();
		balc->set_type(type);
		balc->set_balance(amount);
		balc->set_tm(tm_str);
		
	}
	reply.set_allocated_acc(acc_obj);
}
void BankServer::clean_message(const SelectRequest& req, SimpleReply& reply) {
	if (!req.sure()) {
		if (req.id())
			m_users[where_id(req.id())].m_msgs.clear();
		else
			m_db.Manager_msgs.clear();
	}
	reply.set_code(Succeed);
}
void BankServer::leave_message(const LeaveMessageRequest& req, SimpleReply& reply) {
	pair < pair< int, string >, tm > ah;
	ah.first.first = req.msg().id();
	ah.first.second = req.msg().msg_str();
	ah.second = m_db.read_time();
	if (req.to())
		if (!acc_exist(req.to())) {
			reply.set_code(Err_Noid);
			return;
		}
	if (req.to() == req.msg().id()) {
		reply.set_code(Err_ID_Message);
		return;
	}
	if (req.to()) {
		if (10 <= m_users[where_id(req.to())].m_msgs.size()) {
			reply.set_code(Err_FullMessage);
			return;
		}
		m_users[where_id(req.to())].m_msgs.push_back(ah);
	}
	else {
		if (1000 <= m_db.Manager_msgs.size()) {
			reply.set_code(Err_FullMessage);
			return;
		}
		m_db.Manager_msgs.push_back(ah);
	}
	reply.set_code(Succeed);
}
void BankServer::check_message(const SimpleRequest& req, CheckMessageReply& reply) {
	if(req.id())
		reply.set_msg_size(m_users[where_id(req.id())].m_msgs.size());
	else
		reply.set_msg_size(m_db.Manager_msgs.size());
}
void BankServer::receive_message(const SimpleRequest& req,ShowMessageReply& reply) {
	if (req.id()) {
		for (int i = 0; i < m_users[where_id(req.id())].m_msgs.size(); i++) {
			std::ostringstream oss;
			oss << std::put_time(&m_users[where_id(req.id())].m_msgs[i].second, "%Y-%m-%d %H:%M:%S");
			auto tm_str = oss.str();
			UserMessage* msg_obj = reply.add_msgs();
			msg_obj->set_id(m_users[where_id(req.id())].m_msgs[i].first.first);
			msg_obj->set_msg_str(m_users[where_id(req.id())].m_msgs[i].first.second);
			msg_obj->set_tm(tm_str);
		}
	}
	else {
		for (int i = 0; i < m_db.Manager_msgs.size(); i++) {
			std::ostringstream oss;
			oss << std::put_time(&m_db.Manager_msgs[i].second, "%Y-%m-%d %H:%M:%S");
			auto tm_str = oss.str();
			UserMessage* msg_obj = reply.add_msgs();
			msg_obj->set_id(m_db.Manager_msgs[i].first.first);
			msg_obj->set_msg_str(m_db.Manager_msgs[i].first.second);
			msg_obj->set_tm(tm_str);
		}
	}
}
void BankServer::print_holder_list(const EmptyRequest& req, AllAccountsBasicStatusReply& reply) {
	for (int i = 0; i < m_users.size(); i++) {
		AccountMsg* acc_obj = reply.add_accs();
		acc_obj->set_id(m_users[i].m_id);
		acc_obj->set_name(m_users[i].m_name);
		acc_obj->set_type(m_users[i].m_type);
		acc_obj->set_demand_balance(m_users[i].m_demand_balance);
		acc_obj->set_locked(m_users[i].m_locked);
		acc_obj->set_loan(m_users[i].m_loan);
		acc_obj->set_auto_payment(m_users[i].m_auto_payment);
	}
}


BankError BankServer::init() {
	return m_db.init(m_users);
}

bool BankServer::acc_exist(int id) {
	for (int i = 0; i < int(m_users.size()); i++)
		if (m_users[i].m_id == id)
			return true;
	return false;
}
int BankServer::new_account_id(vector<Account>& users) {
	bool flag = true;
	int i = 100;
	while (true) {
		flag = true;
		for (int j = 0; j < users.size(); j++)
			if (users[j].m_id == i) {
				flag = false;
				i++;
				break;
			}
		if (flag == true)
			return i;
	}
}
int BankServer::where_id(int id) {
	for (int i = 0; i < int(m_users.size()); i++)
		if (m_users[i].m_id == id)
			return i;
	return 0;
}
void BankServer::start() {
	count_profit = std::thread(std::bind(&BankServer::count_time_profit, this));
	count_auto_pay = std::thread (std::bind(&BankServer::count_time_auto_pay_loan, this));
	count_user_saving = std::thread(std::bind(&BankServer::count_user_saving_profit, this));
}
tm BankServer::calculate_time(tm original_time, int past_minute) {
	original_time.tm_min += past_minute;
	if (original_time.tm_min >= 60) {
		original_time.tm_min -= 60; original_time.tm_hour++;
		if (original_time.tm_hour >= 24) {
			original_time.tm_hour -= 24; original_time.tm_mday++;
			if (leap_or_common_year(original_time.tm_year)) {
				if (original_time.tm_mon == 2) {
					if (original_time.tm_mday > 29) {
						original_time.tm_mday -= 29; original_time.tm_mon++;
					}
				}
				else {
					if (big_or_small_month(original_time.tm_mon)) {
						if (original_time.tm_mday > 31) {
							original_time.tm_mday -= 31; original_time.tm_mon++;
						}
					}
					else {
						if (original_time.tm_mday > 30) {
							original_time.tm_mday -= 30; original_time.tm_mon++;
						}
					}
				}
			}
			else {
				if (original_time.tm_mon == 2) {
					if (original_time.tm_mday > 28) {
						original_time.tm_mday -= 28; original_time.tm_mon++;
					}
				}
				else {
					if (big_or_small_month(original_time.tm_mon)) {
						if (original_time.tm_mday > 31) {
							original_time.tm_mday -= 31; original_time.tm_mon++;
						}
					}
					else {
						if (original_time.tm_mday > 30) {
							original_time.tm_mday -= 30; original_time.tm_mon++;
						}
					}
				}
			}
			if (original_time.tm_mon > 12) {
				original_time.tm_mon -= 12; original_time.tm_year++;
			}
		}
	}
	return original_time;
}
bool BankServer::reach_time(tm now_time, tm time_limit) {
	if (now_time.tm_year > time_limit.tm_year)
		return true;
	else if (now_time.tm_year < time_limit.tm_year)
		return false;
	else {
		if (now_time.tm_mon > time_limit.tm_mon)
			return true;
		else if (now_time.tm_mon < time_limit.tm_mon)
			return false;
		else {
			if (now_time.tm_mday > time_limit.tm_mday)
				return true;
			else if (now_time.tm_mday < time_limit.tm_mday)
				return false;
			else {
				if (now_time.tm_hour > time_limit.tm_hour)
					return true;
				else if (now_time.tm_hour < time_limit.tm_hour)
					return false;
				else {
					if (now_time.tm_min > time_limit.tm_min)
						return true;
					else if (now_time.tm_min < time_limit.tm_min)
						return false;
					else {
						if (now_time.tm_sec > time_limit.tm_sec)
							return true;
						else if (now_time.tm_sec <= time_limit.tm_sec)
							return false;
					}
				}
			}
		}
	}
	return false;
}
bool BankServer::leap_or_common_year(int year) {
	return (year % 100 != 0 && year % 4 == 0) || (year % 400 == 0);
}
bool BankServer::big_or_small_month(int month) {
	return (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12);
}

void BankServer::user_Login(const LoginRequest& req, LoginReply& reply) {
	if (!acc_exist(req.id())) {
		reply.set_code(bank::Err_Noid);
		return;
	}
	int r = where_id(req.id());
	reply.set_locked(m_users[r].m_locked);
	if (req.pswd() != m_users[r].m_password) {
		reply.set_code(bank::Err_Login_User_Pswd);
		return;
	}
	else {
		reply.set_code(bank::Succeed);
		reply.set_name(m_users[r].m_name);
		return;
	}
}
void BankServer::manage_Login(const LoginRequest& req, LoginReply& reply) {
	if (req.pswd() != m_db.Manager_password) {
		reply.set_code(bank::Err_Manager_Login);
		return;
	}
	reply.set_code(bank::Succeed);
	reply.set_name(m_db.Manager_name);
}

void BankServer::new_account(const CreateAccountRequest& req, CreateAccountReply& reply) {
	read_write_lock.lock();

	// create account
	int id = new_account_id(m_users);
	Account INP(id, req.name(), req.type(), req.balance(), req.pswd(), 0);
	m_users.push_back(INP);
	m_db.write(m_users);

	// fill in reply
	reply.set_code(bank::Succeed);
	reply.set_id(id);
	std::cout << "ID : " << id << " Create." << endl;
	read_write_lock.unlock();
}
void BankServer::demand_deposit(const UserDemandRequest& req, SimpleReply& reply) {
	read_write_lock.lock();
	if (req.amount() < 0) {
		reply.set_code(Err_Negative_Amount);
		read_write_lock.unlock();
		return;
	}
	m_users[where_id(req.id())].m_demand_balance += req.amount();
	m_db.write(m_users);
	reply.set_code(Succeed);
	std::cout << "ID : " << req.id() << " -> Bank " << req.amount() << " BIL." << endl;
	read_write_lock.unlock();
}
void BankServer::saving_deposit(const UserSavingDepositRequest& req, SimpleReply& reply) {
	read_write_lock.lock();
	pair<TypeOfSavings, double> saving_pair(Minutes_5, 0);
	saving_pair.first = req.type(), saving_pair.second = req.amount();
	tm time = m_db.read_time();
	m_users[where_id(req.id())].m_saving_balance.push_back(pair < pair< TypeOfSavings, double >, tm>(saving_pair, calculate_time(time, change_between_int_and_TypeOfSavings(req.type()))));
	m_db.write(m_users);
	reply.set_code(Succeed);
	std::cout << "ID : " << req.id() << " -> Bank " << req.amount() << " BIL For " << change_between_int_and_TypeOfSavings(req.type()) << " Mins." << endl;
	read_write_lock.unlock();
}
void BankServer::demand_withdraw(const UserDemandRequest& req, SimpleReply& reply) {
	read_write_lock.lock();
	if (req.amount() < 0) {
		reply.set_code(Err_Negative_Amount);
		read_write_lock.unlock();
		return;
	}
	if (m_users[where_id(req.id())].m_demand_balance - req.amount() < 0) {
		reply.set_code(Err_Over_Draft);
		read_write_lock.unlock();
		return;
	}
	m_users[where_id(req.id())].m_demand_balance -= req.amount();
	m_db.write(m_users);
	reply.set_code(Succeed);
	std::cout << "ID : " << req.id() << " <- Bank " << req.amount() << " BIL." << endl;
	read_write_lock.unlock();
}
void BankServer::saving_withdraw(const UserSavingWithdrawRequest& req, SimpleReply& reply) {
	read_write_lock.lock();
	if (1 <= req.serial() && req.serial() <= m_users[where_id(req.id())].m_saving_balance.size()) {
		reply.set_code(Succeed);
		std::cout << "ID : " << req.id() << " <- Bank A Compulsory Saving." << endl;
		m_users[where_id(req.id())].m_saving_balance.erase(m_users[where_id(req.id())].m_saving_balance.begin() + req.serial() - 1);
		m_db.write(m_users);
		
		read_write_lock.unlock();
		return;
	}
	else {
		reply.set_code(Err_Selection_Input);
		read_write_lock.unlock();
		return;
	}
	read_write_lock.unlock();
}
void BankServer::close_account(const SimpleRequest& req, SimpleReply& reply) {
	read_write_lock.lock();
	if (m_users[where_id(req.id())].m_demand_balance > 0 || m_users[where_id(req.id())].m_loan > 0 || m_users[where_id(req.id())].m_saving_balance.size() > 0) {
		reply.set_code(Err_balance_loan_no_clear);
		read_write_lock.unlock();
		return;
	}
	m_users.erase(m_users.begin() + where_id(req.id()));
	std::cout << "ID : " << req.id() << " Close." << endl;
	reply.set_code(Succeed);
	m_db.write(m_users);
	read_write_lock.unlock();
}
void BankServer::password_change(const ChangePasswordRequest& req, SimpleReply& reply) {
	read_write_lock.lock();
	if (req.password() == m_users[where_id(req.id())].m_password) {
		reply.set_code(Err_seen_used_password);
		read_write_lock.unlock();
		return;
	}
	m_users[where_id(req.id())].m_password = req.password();
	reply.set_code(Succeed);
	m_db.write(m_users);
	read_write_lock.unlock();
}
void BankServer::amount_transfer(const UserTransferRequest& req, SimpleReply& reply) {
	read_write_lock.lock();
	if (req.amount() < 0) {
		reply.set_code(Err_Negative_Amount);
		read_write_lock.unlock();
		return;
	}
	if (m_users[where_id(req.original_id())].m_demand_balance - req.amount() < 0) {
		reply.set_code(Err_Over_Draft);
		read_write_lock.unlock();
		return;
	}
	if (!acc_exist(req.transfer_id())) {
		reply.set_code(Err_Noid);
		read_write_lock.unlock();
		return;
	}
	if (m_users[where_id(req.transfer_id())].m_locked == true) {
		reply.set_code(Err_lock);
		read_write_lock.unlock();
		return;

	}
	m_users[where_id(req.original_id())].m_demand_balance -= req.amount(), m_users[where_id(req.transfer_id())].m_demand_balance += req.amount();
	m_db.write(m_users);
	reply.set_code(Succeed);
	std::cout << "ID : " << req.original_id() << " -> ID : " << req.transfer_id() << " " << req.amount() << " BIL." << endl;
	read_write_lock.unlock();
	return;
}
void BankServer::loan_amount(const UserDemandRequest& req, SimpleReply& reply) {
	read_write_lock.lock();
	if (req.amount() < 0) {
		reply.set_code(Err_Negative_Amount);
		read_write_lock.unlock();
		return;
	}
	if (m_users[where_id(req.id())].m_type == 'O') {
		if (m_users[where_id(req.id())].m_loan + req.amount() > 1000) {
			reply.set_code(Err_Over_Loan);
			read_write_lock.unlock();
			return;
		}
	}
	else if (m_users[where_id(req.id())].m_type == 'H') {
		if (m_users[where_id(req.id())].m_loan + req.amount() > 10000) {
			reply.set_code(Err_Over_Loan);
			read_write_lock.unlock();
			return;
		}
	}
	else if (m_users[where_id(req.id())].m_type == 'N') {
		if (m_users[where_id(req.id())].m_loan + req.amount() > 1000000) {
			reply.set_code(Err_Over_Loan);
			read_write_lock.unlock();
			return;
		}
	}
	m_users[where_id(req.id())].m_loan += req.amount();
	m_db.write(m_users);
	reply.set_code(Succeed);
	std::cout << "ID : " << req.id() << " Loan " << req.amount() << "BIL." << endl;
	read_write_lock.unlock();
}
void BankServer::judge_locked(const SimpleRequest& req, LockedReply& reply) {
	reply.set_locked(m_users[where_id(req.id())].m_locked);
}
void BankServer::loan_payment(const UserLoanPayRequest& req, SimpleReply& reply) {
	read_write_lock.lock();
	switch (req.n()) {
	case 1:
		if (req.amount() < 0) {
			reply.set_code(Err_Negative_Amount);
			read_write_lock.unlock();
			return;
		}
		if (m_users[where_id(req.id())].m_loan - req.amount() < 0) {
			m_users[where_id(req.id())].m_loan = 0;
			reply.set_code(Err_Negative_Loan);
			m_db.write(m_users);
			read_write_lock.unlock();
			return;
		}
		m_users[where_id(req.id())].m_loan -= req.amount();
		std::cout << "ID : " << req.id() << " Pay Loan " << req.amount() << "BIL." << endl;
		read_write_lock.unlock();
		return;
		break;
	case 2:
		if (req.amount() < 0) {
			reply.set_code(Err_Negative_Amount);
			read_write_lock.unlock();
			return;
		}
		m_users[where_id(req.id())].m_auto_payment = req.amount();
		std::cout << "ID : " << req.id() << " Change Auto-Pay To " << req.amount() << "BIL." << endl;
		m_db.write(m_users);
		reply.set_code(Succeed);
		read_write_lock.unlock();
		return;
		break;
	}
	m_db.write(m_users);
	reply.set_code(Succeed);
	read_write_lock.unlock();
}

void BankServer::saving_document_list(const EmptyRequest& req, AllAccountsSavingDocumentReply& reply) {
	for (int i = 0; i < m_users.size(); i++) {
		AccountMsg* acc_obj = reply.add_accs();
		acc_obj->set_id(m_users[i].m_id);
		acc_obj->set_name(m_users[i].m_name);
		acc_obj->set_type(m_users[i].m_type);
		
		for (auto& balance : m_users[i].m_saving_balance) {
			std::ostringstream oss;
			oss << std::put_time(&balance.second, "%Y-%m-%d %H:%M:%S");
			auto tm_str = oss.str();
			auto type = balance.first.first;
			auto amount = balance.first.second;
			SaveBalance* bal = acc_obj->add_balances();
			bal->set_type(type);
			bal->set_balance(amount);
			bal->set_tm(tm_str);

		}
	}
}
void BankServer::manager_details_change(const ChangeManagerRequest& req, SimpleReply& reply) {
	read_write_lock.lock();
	if (!Account::validate(req.name())) {
		reply.set_code(Err_Input_Name);
		read_write_lock.unlock();
		return;
	}
	if (req.pswd() == m_db.Manager_password && req.name() == m_db.Manager_name) {
		reply.set_code(Err_seen_modify_details);
		read_write_lock.unlock();
		return;
	}
	m_db.Manager_name = req.name(), m_db.Manager_password = req.pswd();
	reply.set_code(Succeed);
	m_db.write(m_users);
	read_write_lock.unlock();
	return;
}
void BankServer::lock_account(const SimpleRequest& req, SimpleReply& reply) {
	read_write_lock.lock();
	if (!acc_exist(req.id())) {
		reply.set_code(Err_Noid);
		read_write_lock.unlock();
		return;
	}
	if (m_users[where_id(req.id())].m_locked == 1) {
		reply.set_code(Err_already_lock);
		read_write_lock.unlock();
		return;
	}
	m_users[where_id(req.id())].m_locked = 1;
	m_db.write(m_users);
	reply.set_code(Succeed);
	read_write_lock.unlock();
	std::cout << "ID : " << req.id() << " Locked. " << endl;
	return;
}
void BankServer::unlock_account(const SimpleRequest& req, SimpleReply& reply) {
	read_write_lock.lock();
	if (!acc_exist(req.id())) {
		reply.set_code(Err_Noid);
		read_write_lock.unlock();
		return;
	}
	if (m_users[where_id(req.id())].m_locked == 0) {
		reply.set_code(Err_already_unlock);
		read_write_lock.unlock();
		return;
	}
	m_users[where_id(req.id())].m_locked = 0;
	reply.set_code(Succeed);
	m_db.write(m_users);
	std::cout << "ID : " << req.id() << " Unlocked. " << endl;
	read_write_lock.unlock();
	return;
}
void BankServer::toexit(const EmptyRequest& req, EmptyReply& reply) {
	read_write_lock.lock();
	m_db.write(m_users);
	read_write_lock.unlock();
}


void BankServer::count_time_profit() {
	while (true) {
		sleep_for(seconds(60));
		count_lending_profit();
		read_write_lock.lock();
		m_db.write(m_users);
		read_write_lock.unlock();
	}
}
void BankServer::count_lending_profit() {
	for (int i = 0; i < m_users.size(); i++) {
		switch (m_users[i].m_type) {
		case 'N':
			m_users[i].m_loan *= 1.0227;
			break;
		case 'H':
			m_users[i].m_loan *= 1.0375;
			break;
		case 'O':
			m_users[i].m_loan *= 1.0419;
		default:
			m_users[i].m_loan *= 1.0419;
			break;
		}
	}
}
void BankServer::count_time_auto_pay_loan() {
	while (true) {
		sleep_for(seconds(60));
		count_auto_pay_loan();
		read_write_lock.lock();
		m_db.write(m_users);
		read_write_lock.unlock();
	}
}
void BankServer::count_auto_pay_loan() {
	for (int i = 0; i < m_users.size(); i++) {
		if (m_users[i].m_loan == 0)
			continue;
		if (m_users[i].m_demand_balance < m_users[i].m_auto_payment)
			continue;
		if (m_users[i].m_loan < m_users[i].m_auto_payment) {
			m_users[i].m_demand_balance -= m_users[i].m_loan;
			m_users[i].m_loan = 0;
			continue;
		}
		m_users[i].m_loan -= m_users[i].m_auto_payment, m_users[i].m_demand_balance -= m_users[i].m_auto_payment;
	}
}
void BankServer::count_user_saving_profit() {
	while (true) {
		for (int i = 0; i < m_users.size(); i++) {
			for (int j = 0; j < m_users[i].m_saving_balance.size(); j++) {
				if (reach_time(m_db.read_time(), m_users[i].m_saving_balance[j].second)) {
					if (m_users[i].m_saving_balance[j].first.first == Minutes_5)
						switch (m_users[i].m_type) {
						case 'N':
							m_users[i].m_demand_balance += m_users[i].m_saving_balance[j].first.second * 1.0245;
							break;
						case 'H':
							m_users[i].m_demand_balance += m_users[i].m_saving_balance[j].first.second * 1.0188;
							break;
						case 'O':
							m_users[i].m_demand_balance += m_users[i].m_saving_balance[j].first.second * 1.0150;
							break;
						default:
							m_users[i].m_demand_balance += m_users[i].m_saving_balance[j].first.second * 1.0150;
							break;
						}
					else {
						switch (m_users[i].m_type) {
						case 'N':
							m_users[i].m_demand_balance += m_users[i].m_saving_balance[j].first.second * 1.0516;
							break;
						case 'H':
							m_users[i].m_demand_balance += m_users[i].m_saving_balance[j].first.second * 1.0389;
							break;
						case 'O':
							m_users[i].m_demand_balance += m_users[i].m_saving_balance[j].first.second * 1.0303;
							break;
						default:
							m_users[i].m_demand_balance += m_users[i].m_saving_balance[j].first.second * 1.0303;
							break;
						}
					}
					m_users[i].m_saving_balance.erase(m_users[i].m_saving_balance.begin() + j);
				}
				read_write_lock.lock();
				m_db.write(m_users);
				read_write_lock.unlock();
			}
		}
	}
}