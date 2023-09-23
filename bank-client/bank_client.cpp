#include "container.h"
#include "bank_client.h"
#if defined _WIN32
#include <mmsystem.h>
#pragma comment(lib,"WINMM.LIB")
#endif
using std::tm;

BankClient::BankClient(GreeterClient& client) : m_client(client) {
}

void BankClient::print_Bank_introduction() {
	struct bank_information {
		const string Bank_version = "4.0.1";
		const string Bank_tel = "110";
		const string Bank_holder = "Bill Chen";
		const string Bank_update_date = "    Tuesday/15th/June/2021";
	}b_i;
	clear_screen();
	std::cout << "Version : " << b_i.Bank_version << endl;
	std::cout << "Bank Holder : " << b_i.Bank_holder << endl;
	std::cout << "Service Tel : " << b_i.Bank_tel << endl;
	pause_screen();
	std::cout << "System Basic Rules : " << endl;
	std::cout << "	1.Not allowed to input '|' in a name or a password." << endl;
	std::cout << "	2.Not allowed to input to many times uncorrect password." << endl;
	std::cout << "	3.Any helps ? Find manager please." << endl;
	pause_screen();
	std::cout << "	4.Two kinds of Deposit and Withdraw" << endl;

	std::cout << "		Demand 活期:  " << endl;
	std::cout << "			No Interest, Dateless.\n			Initial Balance Decide types of account." << endl;
	std::cout << "			System give savings on the demand." << endl;
	std::cout << "			Demand Withdraw is free." << endl;
	std::cout << "		Saving 定期." << endl;
	std::cout << "			Means Fixed time, Have Interest, Terminable.\n			The main source of income in the account" << endl;
	std::cout << "			Two types of savings : 5 minutes and 10 minutes." << endl;
	std::cout << "			Saving Withdraw need to wait or you will not get interest." << endl;
	pause_screen();

	std::cout << "	5.Three kinds of Account" << endl;

	std::cout << "		Nightshade - Nonpareil(N) :  " << endl;
	std::cout << "		  Initial Saving Balance should greater than 500000 BIL." << endl;
	std::cout << "		  Loan Upper Limit is 1000000 BIL." << endl;
	std::cout << "	        Lending Rate is 2.27 % / min." << endl;
	std::cout << "		  Saving interest is 2.45 % for 5 mins ;  5.16 % for 10 mins" << endl;
	std::cout << "		Hollyhock - High-ranking(H) :  " << endl;
	std::cout << "		  Initial Saving Balance should greater than 50000 BIL." << endl;
	std::cout << "		  Loan Upper Limit is 10000 BIL." << endl;
	std::cout << "		  Lending Rate is 3.75 % / min." << endl;
	std::cout << "		  Saving interest is 1.88 % for 5 mins ;  3.89 % for 10 mins" << endl;
	std::cout << "		Okra - Ordinary (O) :  " << endl;
	std::cout << "		  Initial Saving Balance should greater than 500 BIL." << endl;
	std::cout << "		  Loan Upper Limit is 1000 BIL." << endl;
	std::cout << "		  Lending Rate is 4.19 %." << endl;
	std::cout << "		  Saving interest is 1.50 % for 5 mins ;  3.03 % for 10 mins" << endl;
	pause_screen();

	std::cout << "-- Boss " << b_i.Bank_holder << " and Manager in " << b_i.Bank_update_date << endl;
	pause_screen();
}
void BankClient::print_self_details(int id, string name) {
	if (!id) {
		std::cout << "MANAGER NAME : " << name << endl;
	}
		
	else {
		std::cout << "USER ID   : " << id << endl;
		std::cout << "USER NAME : " << name << endl;
	}
}
void BankClient::print_manager_details(string name) {
	std::cout << "---MANAGER STATUS---" << endl;
	std::cout << endl;
	std::cout << "Manager Name     : " << name << endl;
}
void BankClient::print_account_status(int id) {
	SimpleRequest req;
	ShowAccountReply reply;
	req.set_id(id);
	m_client.ShowAccount(req, reply);

	std::cout << "---ACCOUNT BASIC STATUS---" << endl;
	std::cout << endl;
	std::cout << "Account ID          : " << reply.acc().id() << endl;
	std::cout << "Account Name        : " << reply.acc().name() << endl;
	std::cout << "Account Type        : " << (char)(reply.acc().type()) << endl;
	std::cout << "Account Locked      : " << reply.acc().locked() << endl;
	std::cout.setf(ios::fixed);
	std::cout << "Demand Balance      : " << setprecision(3) << reply.acc().demand_balance() << endl;
	std::cout.setf(ios::fixed);
	std::cout << "Loan Amount         : " << setprecision(3) << reply.acc().loan() << endl;
	std::cout.setf(ios::fixed);
	std::cout << "Auto Payment/min    : " << setprecision(3) << reply.acc().auto_payment() << endl;
	std::cout << endl;
	std::cout << "---SAVING DOCUMENT---" << endl;
	std::cout << endl;
	double sum = 0;
	for (int i = 0; i < reply.acc().balances_size(); i++)
		sum += reply.acc().balances(i).balance();
	cout.setf(ios::fixed);
	cout << "Saving " << setprecision(3) << sum << " BIL in total. " << endl;
	for (int i = 0; i < reply.acc().balances_size(); i++) {
		cout.setf(ios::fixed);
		cout << " --" << i + 1 << ". " << setprecision(3) << reply.acc().balances(i).balance() << " BIL For " << change_between_TyoeOfSavings_and_string(reply.acc().balances(i).type()) << " Which Will Withdraw At ";
		color(14);
		print_time(reply.acc().balances(i).tm());
		color(7);
	}
}
void BankClient::print_time(string time) {
	std::cout << "UTC " << time << endl;
}
void BankClient::print_start() {
	std::thread print_tm(std::bind(&BankClient::print_t, this));
	for (int i = 0; i < 9; i++)
		std::cout << endl;
	std::cout << "                                   BILL'S BANK" << endl;
	std::cout << "                          ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
	std::cout << "                          ┃            BANK            ┃" << endl;
	std::cout << "                          ┃         MANAGEMENT         ┃" << endl;
	std::cout << "                          ┃           SYSTEM           ┃" << endl;
	std::cout << "                          ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ " << endl;
	std::cout << "                               MADE BY : BILL CHEN" << endl;
	sleep_for(seconds(2));
	start();
	clear_screen();
	
}
void BankClient::print_Err(BankError error) {
	color(12);
	switch (error) {
	case Succeed:
		color(10);
		std::cout << "SUCCESS !" << endl;
		break;
	case Err_Initial_Balance_Match_Type:
		std::cout << "ERROR ! UNMATCHING TYPE AND BALANCE !" << endl;
		break;
	case Err_Selection_Input:
		std::cout << "ERROR ! WRITE CORRECT NUMBER ! " << endl;
		break;
	case Err_Input_Name:
		std::cout << "ERROR ! IT IS NOT ALLOWED TO INPUT '|' IN A NAME ! " << endl;
		break;
	case Err_Nofile:
		std::cout << "ERROR ! FAILED TO READ DATA ! " << endl;
		return;
		break;
	case Err_Over_Draft:
		std::cout << "ERROR ! OVERDRAFTED IS NOT ALLOWED ! " << endl;
		break;
	case Err_Over_Loan:
		std::cout << "ERROR ! OVER LOAN < <= 1000 - O ; <= 10000 - H ; <= 1000000 - H > !" << endl;
		break;
	case Err_Negative_Loan:
		std::cout << "ERROR ! NEGATIVE LOAN IS NOT ALLOWED ! " << endl;
		print_War("<== You Payed Off All The Loan ! ");
		break;
	case Err_Pswd:
		std::cout << "ERROR ! IT IS NOT ALLOWED TO INPUT '|' IN A PASSWORD ! " << endl;
		break;
	case Err_Noid:
		std::cout << "ERROR ! CAN NOT FIND THE ID !" << endl;
		break;
	case Err_lock:
		std::cout << "SORRY ! THE ACCOUNT IS LOCKED NOW !" << endl;
		break;
	case Err_Negative_Amount:
		std::cout << "ERROR ! NEGATIVE BALANCE IS NOT ALLOWED ! " << endl;
		break;
	case Err_Login_User_Pswd:
		std::cout << "ERROR ! FAILED TO LOGIN USER ! " << endl;
		break;
	case Err_NoType:
		std::cout << "ERROR ! NO THIS TYPE ! " << endl;
		break;
	case Err_Manager_Login:
		std::cout << "ERROR ! YOU FAILED TO LOGIN MANGER ! " << endl;
		break;
	case Err_already_lock:
		std::cout << "ERROR ! THA ACCOUNT WAS ALREADY LOCKED ! " << endl;
		break;
	case Err_already_unlock:
		std::cout << "ERROR ! THA ACCOUNT WAS ALREADY UNLOCKED ! " << endl;
		break;
	case Err_seen_used_password:
		std::cout << "ERROR ! PLEASE USE DIFFERENT PASSWORD ! " << endl;
		break;
	case Err_seen_modify_details:
		std::cout << "ERROR ! PLEASE USE DIFFERENT DETAILS ! " << endl;
		break;
	case Err_balance_loan_no_clear:
		std::cout << "ERROR ! LOAN AND BALANCE HAVE NOT BE CLEAND ! " << endl;
		break;
	case Err_FullMessage:
		std::cout << "ERROR ! YOU TARGET IS FULL MESSAGE ! " << endl;
		break;
	case Err_ID_Message:
		std::cout << "ERROR ! YOU CAN NOT SEND MESSAGE TO YOURSELF !" << endl;
		break;
	default:
		std::cout << "UNKNOWN ERROR !" << endl;
		break;
	}
	color(7);
	pause_screen();
	return;
}
void BankClient::print_holder_list() {
	EmptyRequest req;
	AllAccountsBasicStatusReply reply;
	m_client.AllAccountsBasicStatus(req, reply);
	std::cout << endl;
	std::cout << "                            - ACCOUNT HOLDER LIST -" << endl;
	std::cout << "===============================================================================" << endl;
	std::cout << "ID" << setw(10) << "Name" << setw(10) << "Type" << setw(20) << "Balance" << setw(10) << "Locked" << setw(10) << "Loan" << setw(10) << "Auto-Pay" << endl;
	std::cout << "===============================================================================" << endl;
	std::cout.setf(ios::fixed);
	for (int i = 0; i < reply.accs_size(); i++)
		std::cout << reply.accs(i).id() << setw(8) << reply.accs(i).name() << setw(10) << (char)(reply.accs(i).type()) << setw(20) << setprecision(3) << reply.accs(i).demand_balance() << setw(10) << reply.accs(i).locked() << setw(10) << setprecision(3) << reply.accs(i).loan() << setw(10) << reply.accs(i).auto_payment() << endl;
}
void BankClient::print_greet_to_manager() {
	std::cout << "Hi, My Dear Manager ." << endl;
	pause_screen();
}
int BankClient::print_loan_pay_menu() {
	int input_loan_pay_n;
	std::cout << endl;
	std::cout << "01. MANUAL PAYMENT" << endl;
	std::cout << "02. AUTOMATIC PAYMENT" << endl;
	std::cout << "Select Your Option <1-2> : ";
	std::cin >> input_loan_pay_n;
	cout << endl << endl;
	return input_loan_pay_n;
}
int BankClient::print_savings_menu() {
	int input_savings_n;
	std::cout << endl << endl;
	std::cout << "01. 5 MINS SAVINGS" << endl;
	std::cout << "02. 10 MINS SAVINGS" << endl;
	std::cout << "Select Your Option <1-2> : ";
	std::cin >> input_savings_n;
	cout << endl << endl;
	return input_savings_n;
}
int BankClient::print_saving_or_demand_menu() {
	int input_savings_or_demand_n;
	std::cout << endl;
	std::cout << "01. DEMAND TYPE" << endl;
	std::cout << "02. TERMINAL TYPE" << endl;
	std::cout << "03. EXIT" << endl;
	std::cout << "Select Your Option <1-3> : ";
	std::cin >> input_savings_or_demand_n;
	cout << endl;
	return input_savings_or_demand_n;
}

void BankClient::start() {
	clear_screen();
	while (true)
		main_menu();
}

pair<int, string> BankClient::user_Login() {
	LoginRequest req;
	LoginReply reply;
	string pswd;
	int id;
	clear_screen();
	std::cout << "---USER LOGIN FORM---" << endl;
	std::cout << "==> Enter User-ID : ";
	std::cin >> id;
	// create request and reply
	req.set_id(id);
	std::cout << "==> Enter User-Password : ";
	pswd = secretword();
	req.set_pswd(pswd);
	m_client.UserLogin(req, reply);
	if (reply.locked() == 1) {
		print_Err(Err_already_lock);
		return pair<int, string>(-1, "");
	}
	print_Err(reply.code());
	if (reply.code() == Succeed) {
		return pair<int, string>(id, reply.name());
	}
	return pair<int, string>(-1, "");
	clear_screen();
}
pair<int, string> BankClient::manage_Login() {
	LoginRequest req;
	req.set_id(0);
	LoginReply reply;
	string pswd;
	
	clear_screen();
	std::cout << "---MANAGER LOGIN FORM---" << endl;
	std::cout << "==> Enter Manager-Password : ";
	pswd = secretword();
	req.set_pswd(pswd);
	m_client.ManagerLogin(req, reply);
	print_Err(reply.code());
	
	if (reply.code() == Succeed) {
		return pair<int, string>(0, reply.name());
	}
	return pair<int, string>(-1, "");
}

void BankClient::print_check_message(TypeOfAccount type, int id) {
	SimpleRequest req;
	CheckMessageReply reply;
	int size;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pair<int, int> XY = GetXY();
	while (ref) {
		req.set_id(id);
		m_client.CheckMessage(req, reply);
		size = reply.msg_size();
		XY = GetXY();
		if (type == Type_User) {
			pos = { 53,15 };
			SetConsoleCursorPosition(hOut, pos);
			if (10 <= size) {
				color(13);
				cout << " FULL";
				color(7);
			}
			else if (size > 0) {
				color(11);
				cout << " NEW " << size;
				color(7);
			}
			else {
				cout << "        ";
			}
				
		}
		else {
			pos = { 49,13 };
			SetConsoleCursorPosition(hOut, pos);
			if (1000 <= size) {
				color(13);
				cout << " FULL";
				color(7);
			}
			else if (size > 0) {
				color(11);
				cout << " NEW " << size;
				color(7);
			}
			else {
				cout << "         ";
			}
		}
		pos = { (short)XY.first,(short)XY.second };
		SetConsoleCursorPosition(hOut, pos);
		sleep_for(seconds(1));
	}
	
}
pair<int, int> BankClient::GetXY()
{
	HANDLE hStdout;
	CONSOLE_SCREEN_BUFFER_INFO pBuffer;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hStdout, &pBuffer);
	return pair<int, int>(pBuffer.dwCursorPosition.X, pBuffer.dwCursorPosition.Y);
}
void BankClient::show_menu(TypeOfAccount type, int id, string name) {
	clear_screen();
	//HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//pair<int,int> XY = GetXY();
	//SetConsoleCursorPosition(hOut, pos);
	switch (type) {
		case Type_Manager:
			print_self_details(0, name);
			std::cout << endl << endl << endl << endl << endl << endl;
			std::cout << "                                  -MANAGER MENU-" << endl;
			std::cout << "                             01. ALL ACCOUNT BASIC HOLDER LIST" << endl;
			std::cout << "                             02. ALL ACCOUNT TERMINAL SAVING DOCUMENT"<< endl;
			std::cout << "                             03. LOCK ACCOUNT" << endl;
			std::cout << "                             04. UNLOCK ACCOUNT" << endl;
			std::cout << "                             05. MANAGER DETAILS CHANGE" << endl;
			std::cout << "                             06. RECEIVE MESSAGES" << endl;
			std::cout << "                             07. LEAVE MESSAGES" << endl;
			std::cout << "                             08. LOGOUT" << endl;
			std::cout << "                             09. EXIT SYSTEM" << endl;
			std::cout << "                           Select Your Option <1-9> : ";
			break;
		case Type_User:
			print_self_details(id, name);
			std::cout << endl << endl << endl << endl;
			std::cout << "                                   -USER MENU-" << endl;
			std::cout << "                                01. DEPOSIT AMOUNT" << endl;	
			std::cout << "                                02. WITHDRAW AMOUNT" << endl;
			std::cout << "                                03. BALANCE ENQUIRY" << endl;
			std::cout << "                                04. CLOSE AN ACCOUNT" << endl;
			std::cout << "                                05. CHANGE PASSWORD" << endl;
			std::cout << "                                06. TRANSFER AMOUNT" << endl;
			std::cout << "                                07. LOAN AMOUNT" << endl;
			std::cout << "                                08. LOAN PAYMENT" << endl;	
			std::cout << "                                09. RECEIVE MESSAGES" << endl;
			std::cout << "                                10. LEAVE MESSAGES" << endl;
			std::cout << "                                11. LOGOUT" << endl;
			std::cout << "                              Select Your Option <1-11> : ";
			break;
		default:
			break;
	}
	ref = true;
	std::thread refresh_msg(std::bind(&BankClient::print_check_message, this, type, id));
	refresh_msg.detach();
	return;
}
bool BankClient::do_menu(TypeOfAccount type, int id, int n) {
	//True means logout
	if (type == Type_Manager) {
		switch (n) {
		case 1:
			holder_list();
			break;
		case 2:
			saving_document_list();
			break;
		case 3:
			lock_account();
			break;
		case 4:
			unlock_account();
			break;
		case 5:
			manager_details_change();
			break;
		case 6:
			receive_message(0);
			break;
		case 7:
			leave_message(0);
			break;
		case 8:
			return true;
			break;
		case 9:
			toexit();
			break;
		default:
			print_Err(Err_Selection_Input);
			break;
		}
	}
	else {
		switch (n) {
		case 1:
			deposit(id);
			break;
		case 2:
			withdraw(id);
			break;
		case 3:
			balance_enquiry(id);
			break;
		case 4:
			return close_account(id);
			break;
		case 5:
			password_change(id);
			break;
		case 6:
			amount_transfer(id);
			break;
		case 7:
			loan_amount(id);
			break;
		case 8:
			loan_payment(id);
			break;
		case 9:
			receive_message(id);
			break;
		case 10:
			leave_message(id);
			break;
		case 11:
			return true;
			break;
		default:
			print_Err(Err_Selection_Input);
			break;
		}
	}
	return false;
}
void BankClient::print_t() {
	while (true) {
		time_t t = time(NULL);
		time(&t);
		tm* usc_t = gmtime(&t);
		std::ostringstream oss;
		oss << std::put_time(usc_t, "%Y-%m-%d %H:%M:%S");
		std::wstring tm_str = L"Bank-Client : UTC " + utf8ToUtf16(oss.str());
		SetConsoleTitle(tm_str.c_str());
		//system(tm_str.c_str());
		sleep_for(seconds(1));
	}
}
wstring BankClient::utf8ToUtf16(const std::string& utf8Str) {
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
	return conv.from_bytes(utf8Str);
}
void BankClient::music_state(bool flag) {
	if (flag)
		//PlaySound(TEXT("Bill_music.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		return;
	else
		PlaySound(NULL, NULL, SND_PURGE);
}
void BankClient::main_menu() {
	int main_n;
	int n;
	pair<int, string> user_login_judge;
	pair<int, string> manager_login_judge;
	SimpleRequest req;
	LockedReply reply;
	clear_screen();
	std::cout << endl << endl << endl << endl << endl << endl << endl << endl;
	std::cout << "                                   -MAIN MENU-" << endl;
	std::cout << "                                01. NEW ACCOUNT" << endl;
	std::cout << "                                02. USER LOGIN" << endl;
	std::cout << "                                03. MANAGER LOGIN" << endl;
	std::cout << "                                04. BANK DETAILS" << endl;
	std::cout << "                              Select Your Option <1-4> : ";
	std::cin >> main_n;
	switch (main_n) {
	case 1:
		music_state(true);
		new_account();
		music_state(false);
		break;
	case 2:
		user_login_judge = user_Login();
		if (user_login_judge.first != -1) {
			music_state(true);
			while (true) {
				show_menu(Type_User, user_login_judge.first, user_login_judge.second);
				cin >> n;
				ref = false;
				req.set_id(user_login_judge.first);
				m_client.JudgeLocked(req, reply);
				if (reply.locked() == 1) {
					print_Err(Err_already_lock);
					break;
				}
				if (do_menu(Type_User, user_login_judge.first, n))
					break;
				
			}
			music_state(false);
		}
		break;
	case 3:
		manager_login_judge = manage_Login();
		if (manager_login_judge.first != -1) {
			music_state(true);
			while (true) {
				show_menu(Type_Manager, manager_login_judge.first, manager_login_judge.second);
				cin >> n;
				ref = false;
				if (do_menu(Type_Manager, manager_login_judge.first, n))
					break;
			}
			music_state(false);
		}
		break;
	case 4:
		music_state(true);
		print_Bank_introduction();
		music_state(false);
		break;
	default:
		print_Err(Err_Selection_Input);
		main_n = 0;
		break;
	}
	return;
}


void BankClient::new_account() {
	string INP_name = "";
	char INP_type = '\0';
	double INP_amount = 0;
	string INP_password = "";
	char type = 0;
	double balance = 0;
	clear_screen();
	std::cout << "---NEW ACCOUNT ENTRY FORM---" << endl;
	std::cout << "-NEW ACCOUNT-" << endl ;
	std::cout << "==> Enter User-Name : ";
	std::cin >> INP_name;
	while (!Account::validate(INP_name)) {
		print_Err(Err_Input_Name);
		cout << "==> Enter User-Name Again : ";
		cin >> INP_name;
	}
	
	INP_password = Account::new_password();
	while (INP_password == "") {
		INP_password = Account::new_password();
	}
	while (true) {
		std::cout << "==> Enter User-Type <O/H/N>" << endl;
		cout << "\t--< Okra , Hollyhock , Nightshade > : ";
		std::cin >> type;
		while (type != 'H' && type != 'N' && type != 'O') {
			print_Err(Err_NoType);
			std::cout << "==> Enter User-Type <O/H/N> Again : ";
			std::cin >> type;
		}
		std::cout << "==> Enter Initial-Balance " << endl << "\t--< >=500 - O ; >=50000 - H ; >= 500000 - N> : ";
		std::cin >> balance;
		while (balance < 0) {
			print_Err(Err_Negative_Amount);
			std::cout << "==> Enter Initial-Balance Again : ";
			std::cin >> balance;
		}
		bool ok;
		if (type == 'O')
			if (balance >= 500)
				ok = true;
			else
				ok = false;
		else if (type == 'H')
			if (balance >= 50000)
				ok = true;
			else
				ok = false;
		else if (type == 'N')
			if (balance >= 500000)
				ok = true;
			else
				ok = false;
		if (ok == true) {
			break;
		}
		else {
			print_Err(Err_Initial_Balance_Match_Type);
			print_War("<== You Need To Enter Again !");
		}
	}

	// create request and reply
	CreateAccountRequest req;
	CreateAccountReply reply;
	req.set_name(INP_name);
	req.set_pswd(INP_password);
	req.set_type(type);
	req.set_balance(balance);

	m_client.CreateAccount(req, reply);
	if (reply.code() != Succeed)
		print_Err(reply.code());
	else {
		color(14);
		std::cout << "<== Your New ID Will be : ";
		std::cout << reply.id() << endl;
		color(7);
		print_Err(reply.code());
	}
	clear_screen();
}
void BankClient::print_War(string warning) {
	color(14);
	std::cout << warning << endl;
	color(7);
}
void BankClient::deposit(int id) {
	clear_screen();
	std::cout << "---ACCOUNT TRANSCATION FORM---" << endl;
	std::cout << "-DEPOSIT AMOUNT-" << endl << endl;
	print_account_status(id);
	int deposit_n = print_saving_or_demand_menu();
	switch (deposit_n) {
	case 1:
		demand_deposit(id);
		break;
	case 2:
		saving_deposit(id);
		break;
	case 3:
		print_Err(Succeed);
		break;
	default:
		print_Err(Err_Selection_Input);
		break;
	}
}
void BankClient::demand_deposit(int id) {
	UserDemandRequest req;
	SimpleReply reply;
	double amount;
	clear_screen();
	std::cout << "---ACCOUNT TRANSCATION FORM---" << endl;
	std::cout << "-DEPOSIT AMOUNT-" << endl;
	std::cout << "-DEMAND-" << endl << endl;
	print_account_status(id);
	std::cout << "==> Enter Demand Deposit Amount : ";
	std::cin >> amount;
	req.set_amount(amount);
	req.set_id(id);
	m_client.UserDemandDeposit(req, reply);
	print_Err(reply.code());
}
void BankClient::saving_deposit(int id) {
	UserSavingDepositRequest req;
	SimpleReply reply;
	req.set_id(id);
	clear_screen();
	std::cout << "---ACCOUNT TRANSCATION FORM---" << endl;
	std::cout << "-DEPOSIT AMOUNT-" << endl;
	std::cout << "-SAVING-" << endl << endl;
	print_account_status(id);
	double amount = 0;
	std::cout << "==> Enter Saving Deposit Amount : ";
	std::cin >> amount;
	if (amount < 0) {
		print_Err(Err_Negative_Amount);
		return;
	}
	req.set_amount(amount);
	switch (print_savings_menu()) {
	case 1:
		req.set_type(Minutes_5);
		m_client.UserSavingDeposit(req, reply);
		break;
	case 2:
		req.set_type(Minutes_10);
		m_client.UserSavingDeposit(req, reply); 
		break;
	default:
		print_Err(Err_Selection_Input);
		return;
		break;
	}
	print_Err(reply.code());
}

void BankClient::withdraw(int id) {
	clear_screen();
	std::cout << "---ACCOUNT TRANSCATION FORM---" << endl;
	std::cout << "-WITHDRAW AMOUNT-" << endl << endl;
	print_account_status(id);
	int withdraw_n = print_saving_or_demand_menu();
	switch (withdraw_n) {
	case 1:
		demand_withdraw(id);
		break;
	case 2:
		saving_withdraw(id);
		break;
	case 3:
		print_Err(Succeed);
		break;
	default:
		print_Err(Err_Selection_Input);
		break;
	}
}
void BankClient::demand_withdraw(int id) {
	UserDemandRequest req;
	SimpleReply reply;
	double amount;
	clear_screen();
	std::cout << "---ACCOUNT TRANSCATION FORM---" << endl;
	std::cout << "-WITHDRAW AMOUNT-" << endl;
	std::cout << "-DEMAND-" << endl << endl;
	print_account_status(id);
	std::cout << "==> Enter Demand Withdraw Amount : ";
	std::cin >> amount;
	req.set_amount(amount);
	req.set_id(id);
	m_client.UserDemandWithdraw(req, reply);
	print_Err(reply.code());
}
void BankClient::saving_withdraw(int id) {
	UserSavingWithdrawRequest req;
	SimpleReply reply;
	int serial_number;
	int sure;
	req.set_id(id);
	clear_screen();
	std::cout << "---ACCOUNT TRANSCATION FORM---" << endl;
	std::cout << "-WITHDRAW AMOUNT-" << endl;
	std::cout << "-SAVING-" << endl << endl;
	print_War("<== You Are In Compulsorily Withdraw Undue Savings Type Now !");
	print_War("<== You Will Lose Your Interest !");
	print_War("<== If You Exit , System Will Automatically Transferring Mature Money To Your Demand Balance.");
	std::cout << endl;
	print_account_status(id);
	std::cout << "==> Do You Sure To Continue ? < 0  Sure > : ";
	std::cin >> sure;
	if (sure)
		return;
	std::cout << endl;
	std::cout << "==> Enter Compulsorily Withdraw Savings-Serial Number: ";
	std::cin >> serial_number;
	std::cout << endl;
	req.set_serial(serial_number);
	m_client.UserSavingWithdraw(req, reply);
	print_Err(reply.code());
}
void BankClient::balance_enquiry(int id) {
	clear_screen();
	std::cout << "---BALANCE DETAILS---" << endl;
	std::cout << "-BALANCE ENQUIRY-" << endl << endl;
	sleep_for(microseconds(800));
	print_account_status(id);
	pause_screen();
}
bool BankClient::close_account(int id) {
	SimpleRequest req;
	SimpleReply reply;
	int sure;
	clear_screen();
	std::cout << "---DELETE RECORD---" << endl;
	std::cout << "-CLOSE ACCOUNT-" << endl << endl;
	print_War("<== You Will Lose Your Account !");
	pause_screen();
	print_account_status(id);
	req.set_id(id);
	std::cout << "==> Do You Sure To Continue ? < 0  Sure > : ";
	std::cin >> sure;
	if (sure)
		return false;
	m_client.CloseAccount(req, reply);
	print_Err(reply.code());
	if (reply.code() == Succeed)
		return true;
	return false;
}
void BankClient::password_change(int id) {
	ChangePasswordRequest req;
	SimpleReply reply;
	clear_screen();
	string password;
	std::cout << "---ACCOUNT PASSWORD CHANGE FORM---" << endl;
	std::cout << "-PASSWORD CHANGE-" << endl << endl;
	print_account_status(id);
	password = Account::new_password();
	while (password == "") {
		password = Account::new_password();
	}
	req.set_id(id);
	req.set_password(password);
	m_client.ChangePassword(req, reply);
	print_Err(reply.code());
}
void BankClient::amount_transfer(int id) {
	UserTransferRequest req;
	SimpleReply reply;
	clear_screen();
	req.set_original_id(id);
	int transfer_id;
	double amount;
	std::cout << "---ACCOUNT TRANSCATION FORM---" << endl;
	std::cout << "-TRANSFER AMOUNT-" << endl << endl;
	print_account_status(id);
	std::cout << "==> Enter Transfer/Receives-ID : ";
	std::cin >> transfer_id;
	std::cout << "==> Enter Transfer-Amount : ";
	std::cin >> amount;
	req.set_amount(amount);
	req.set_transfer_id(transfer_id);
	m_client.UserTransfer(req, reply);
	print_Err(reply.code());
}
void BankClient::loan_amount(int id) {
	UserDemandRequest req;
	SimpleReply reply;
	clear_screen();
	double amount;
	std::cout << "---ACCOUNT TRANSCATION FORM---" << endl;
	std::cout << "-LOAN AMOUNT-" << endl << endl;
	print_account_status(id);
	std::cout << "==> Enter Loan-Amount : ";
	std::cin >> amount;
	req.set_id(id);
	req.set_amount(amount);
	m_client.UserLoan(req, reply);
	print_Err(reply.code());
}
void BankClient::loan_payment(int id) {
	clear_screen();
	UserLoanPayRequest req;
	SimpleReply reply;
	req.set_id(id);
	double amount;
	std::cout << "---ACCOUNT TRANSCATION FORM---" << endl;
	std::cout << "-LOAN PAYMENT-" << endl << endl;
	print_account_status(id);
	
	int loan_pay_n = print_loan_pay_menu();
	switch (loan_pay_n) {
	case 1:
		std::cout << "==> Enter Loan Payment-Amount : ";
		std::cin >> amount;
		req.set_amount(amount);
		req.set_n(loan_pay_n);
		m_client.UserLoanPay(req, reply);
		print_Err(reply.code());
		break;
	case 2:
		print_War("<== Input 0 If You Don't Want An Automatic Payment . ");
		std::cout << "==> Modify Loan Auto Payment / Min : ";
		std::cin >> amount;
		req.set_amount(amount);
		req.set_n(loan_pay_n);
		m_client.UserLoanPay(req, reply);
		print_Err(reply.code());
		break;
	default:
		print_Err(Err_Selection_Input);
		break;
	}
}
void BankClient::leave_message(int id) {
	clear_screen();
	std::cout << "---MESSAGE SYSTEM---" << endl;
	std::cout << "-LEAVE MESSAGE-";
	std::cout << endl << endl;
	LeaveMessageRequest req;
	SimpleReply reply;
	int to_id;
	string input_tool;
	string message;
	if (id) 
		print_War("<== Enter 0 If You Want To Connect With Manager !");
	else
		print_greet_to_manager();
	std::cout << endl;
	std::cout << "==> Enter Target/Receives-ID : ";
	std::cin >> to_id;
	std::cout << "==> Enter Leave-Massege : ";
	getline(cin, input_tool);
	getline(cin, message);
	req.set_to(to_id);
	UserMessage* msg_obj = new UserMessage();
	msg_obj->set_id(id);
	msg_obj->set_msg_str(message);
	req.set_allocated_msg(msg_obj);
	m_client.LeaveMessage(req, reply);
	print_Err(reply.code());
}
void BankClient::receive_message(int id) {
	clear_screen();
	std::cout << "---MESSAGE SYSTEM---" << endl;
	std::cout << "-RECEIVE MESSAGE-";
	std::cout << endl << endl;
	SimpleRequest req;
	ShowMessageReply reply;
	SelectRequest req_;
	SimpleReply reply_;
	if (!id)
		print_greet_to_manager();
	std::cout << endl;
	req.set_id(id);
	m_client.ShowMessage(req, reply);
	for (int i = 0; i < reply.msgs_size(); i++) {
		std::cout << i + 1 << ". ";
		color(14);
		cout << "UTC " << reply.msgs(i).tm();
		color(7);
		if(reply.msgs(i).id())
			std::cout << " - ID " << reply.msgs(i).id() << " Send : " << reply.msgs(i).msg_str() << endl;
		else
			std::cout << " - Manager Send : " << reply.msgs(i).msg_str() << endl;
	}
	if (reply.msgs_size() > 0) {
		cout << endl;
		pause_screen();
		std::cout << "==> Do You Want To Clear ? < 0  Sure > : ";
		int sure;
		std::cin >> sure;
		req_.set_sure(sure);
		req_.set_id(id);
		m_client.CleanMessage(req_, reply_);
		print_Err(reply_.code());
	}
	else {
		cout << endl;
		cout << "Nothing." << endl;
		pause_screen();
	}

}
void BankClient::holder_list() {
	clear_screen();
	std::cout << "---HOLDER DETAILS---" << endl;
	std::cout << "-HOLDER LIST-";
	std::cout << endl << endl;
	sleep_for(microseconds(800));
	print_greet_to_manager();
	print_holder_list();
	pause_screen();
	clear_screen();
}
void BankClient::saving_document_list() {
	EmptyRequest req;
	AllAccountsSavingDocumentReply reply;
	clear_screen();
	std::cout << "---SAVING DOCUMENT---" << endl;
	std::cout << "-SAVING DOCUMENT LIST-" << endl << endl;
	print_greet_to_manager();
	m_client.AllAccountsSavingDocument(req, reply);
	cout << "----------------------------------------------" << endl;
	for (int j = 0; j < reply.accs_size(); j++) {
		double sum = 0;	
		cout << "ID : " << reply.accs(j).id() << endl;
		cout << "TYPE : " << (char)(reply.accs(j).type()) << endl;
		cout << "NAME :" << reply.accs(j).name() << endl;
		for (int i = 0; i < reply.accs(j).balances_size(); i++)
			sum += reply.accs(j).balances(i).balance();
		cout.setf(ios::fixed);
		cout << "Saving " << setprecision(3) << sum << " BIL in total. " << endl;
		for (int i = 0; i < reply.accs(j).balances_size(); i++) {
			cout.setf(ios::fixed);
			cout << " --" << i + 1 << ". " << setprecision(3) << reply.accs(j).balances(i).balance() << " BIL For " << change_between_TyoeOfSavings_and_string(reply.accs(j).balances(i).type()) << " Which Will Withdraw At ";
			color(14);
			print_time(reply.accs(j).balances(i).tm());
			color(7);
		}
		std::cout << endl;
		std::cout << "----------------------------------------------" << endl;
		
	}
	pause_screen();
	clear_screen();
}
void BankClient::manager_details_change() {
	ChangeManagerRequest req;
	SimpleReply reply;
	string name, pswd;
	clear_screen();
	std::cout << "---MANAGER DETAILS---" << endl;
	std::cout << "-MANGER DETAILS CHANGE-" << endl << endl;
	print_greet_to_manager();
	std::cout << "---NEW DETAILS---" << endl;
	std::cout << endl;
	std::cout << "==> Enter New Manager-Name : ";
	std::cin >> name;
	req.set_name(name);
	pswd = Account::new_password();
	while (pswd == "") {
		pswd = Account::new_password();
	}
	req.set_pswd(pswd);
	m_client.ChangeManager(req, reply);
	print_Err(reply.code());
}
void BankClient::lock_account() {
	SimpleRequest req;
	SimpleReply reply;
	clear_screen();
	int id;
	std::cout << "---ACCOUNT STATE TRANSITION FORM---" << endl;
	std::cout << "-LOCK ACCOUNT-" << endl << endl;
	print_greet_to_manager();
	std::cout << "==> Enter Target User-ID : ";
	std::cin >> id;
	req.set_id(id);
	m_client.LockUser(req, reply);
	print_Err(reply.code());
}
void BankClient::unlock_account() {
	SimpleRequest req;
	SimpleReply reply;
	clear_screen();
	int id;
	std::cout << "---ACCOUNT STATE TRANSITION FORM---" << endl;
	std::cout << "-UNlOCK ACCOUNT-" << endl << endl;
	print_greet_to_manager();
	std::cout << "==> Enter Target User-ID : ";
	std::cin >> id;
	req.set_id(id);
	m_client.UnlockUser(req, reply);
	print_Err(reply.code());
}
void BankClient::toexit() {
	EmptyRequest req;
	EmptyReply reply;
	clear_screen();
	std::cout << "---EXIT FORM---" << endl;
	std::cout << "-EXIT BANK SYSTEM-" << endl << endl;
	m_client.Exit(req, reply);
	sleep_for(seconds(1));
	std::cout << "See you Next time ." << endl;
	pause_screen();
	exit(0);
}