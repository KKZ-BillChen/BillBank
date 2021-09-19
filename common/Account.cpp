#include "Account.h"

Account::Account(string record) {
	int k = 0;
	m_name = "";
	m_id = 0;
	m_type;
	m_demand_balance = 0;
	m_password = "";
	m_locked = 0;
	m_loan = 0;
	m_auto_payment = 0;
	m_saving_balance.clear();

	// read account num
	string id_string = "";
	while (record[k] != '|') {
		id_string += record[k];
		k++;
		if (record[k] == '|')
			break;
	}
	k++;
	istringstream is3(id_string);
	is3 >> m_id;
	// read account name
	while (record[k] != '|') {
		m_name += record[k];
		k++;
		if (record[k] == '|')
			break;
	}
	k++;
	if (m_id) {
		// read account type
		m_type = record[k];
		string amount_string = "";
		k += 2;
		// read amount balance
		while (record[k] != '|') {
			amount_string += record[k];
			k++;
			if (record[k] == '|')
				break;
		}
		k++;
		m_demand_balance = atof(amount_string.c_str());
		while (record[k] != '|') {
			m_password += record[k];
			k++;
			if (record[k] == '|')
				break;
		}
		k++;
		string locked_str;
		locked_str += record[k];
		m_locked = atoi(locked_str.c_str());
		string loan_string = "";
		k += 2;
		while (record[k] != '|') {
			loan_string += record[k];
			k++;
			if (record[k] == '|')
				break;
		}
		k++;
		m_loan = atof(loan_string.c_str());
		string auto_string;
		while (record[k] != '|') {
			auto_string += record[k];
			k++;
			if (record[k] == '|')
				break;
		}
		m_auto_payment = atof(auto_string.c_str());
		k++;
		string saving_size_string;
		int saving_size = 0;
		while (record[k] != '|') {
			saving_size_string += record[k];
			k++;
			if (record[k] == '|')
				break;
		}
		saving_size = atoi(saving_size_string.c_str());
		k++;
		if (saving_size > 0) {
			for (int i = 0; i < saving_size; i++) {
				string TypeOfSavings_string;
				while (record[k] != '|') {
					TypeOfSavings_string += record[k];
					k++;
					if (record[k] == '|')
						break;
				}
				TypeOfSavings Saving_Type = change_between_TypeOfSavings_and_int(atoi(TypeOfSavings_string.c_str()));
				k++;
				string save_amount_string;
				while (record[k] != '|') {
					save_amount_string += record[k];
					k++;
					if (record[k] == '|')
						break;
				}
				double amount = atof(save_amount_string.c_str());
				k++;
				string year_string;
				while (record[k] != '|') {
					year_string += record[k];
					k++;
					if (record[k] == '|')
						break;
				}
				int year = atoi(year_string.c_str());
				k++;
				string month_string;
				while (record[k] != '|') {
					month_string += record[k];
					k++;
					if (record[k] == '|')
						break;
				}
				int mon = atoi(month_string.c_str());
				k++;
				string mday_string;
				while (record[k] != '|') {
					mday_string += record[k];
					k++;
					if (record[k] == '|')
						break;
				}
				int mday = atoi(mday_string.c_str());
				k++;
				string hour_string;
				while (record[k] != '|') {
					hour_string += record[k];
					k++;
					if (record[k] == '|')
						break;
				}
				int hour = atoi(hour_string.c_str());
				k++;
				string min_string;
				while (record[k] != '|') {
					min_string += record[k];
					k++;
					if (record[k] == '|')
						break;
				}
				int min = atoi(min_string.c_str());
				k++;
				string sec_string;
				while (record[k] != '|') {
					sec_string += record[k];
					k++;
					if (record[k] == '|')
						break;
				}
				int sec = atoi(sec_string.c_str());
				k++;
				struct tm timeread;
				timeread.tm_year = year, timeread.tm_mon = mon, timeread.tm_mday = mday, timeread.tm_hour = hour, timeread.tm_min = min, timeread.tm_sec = sec;
				pair<TypeOfSavings, double> saving_pair_read(Saving_Type, amount);
				m_saving_balance.push_back(pair < pair< TypeOfSavings, double >, tm>(saving_pair_read, timeread));
			}
		}
	}
	else {
		while (record[k] != '|') {
			m_password += record[k];
			k++;
			if (record[k] == '|')
				break;
		}
	}
}
Account::Account(int id, string name, char type, double balance, string pswd, int locked, double loan, double auto_pay) {
	m_id = id;
	m_name = name;
	m_type = type;
	m_demand_balance = balance;
	m_password = pswd;
	m_locked = locked;
	m_loan = loan;
	m_auto_payment = auto_pay;
}

bool Account::validate(string str) {
	for (int i = 0; i < int(str.length()); i++)
		if (str[i] == '|')
			return false;
	return true;
}

string Account::new_password() {
	string pswd1;
	string pswd2;
	std::cout << "==> Enter User/Manager-Password : ";
	pswd1 = secretword();
	if ((pswd1.length() < 6)) {
		color(12);
		std::cout << "ERROR ! NOT CORRECT PASSWORD ! PASSWORD LENGTH > 6 \n";
		color(14);
		std::cout << "<== You Need To Enter Again ! " << endl;
		color(7);
		return "";
	}
	if (!Account::validate(pswd1)) {
		color(12);
		std::cout << "ERROR ! IT IS NOT ALLOWED TO INPUT '|' IN A PASSWORD ! " << endl;
		color(14);
		std::cout << "<== You Need To Enter Again ! " << endl;
		color(7);
		return "";
	}
	std::cout << "==> Enter Sure User/Manager-Password : ";
	pswd2 = secretword();
	if ((pswd1 != pswd2)) {
		color(12);
		std::cout << "ERROR ! NOT CORRECT PASSWORD ! PASSWORDS SHOULD BE THE SAME ! \n";
		color(14);
		std::cout<<"<== You Need To Enter Again ! " << endl;
		color(7);
		return "";
	}
	return pswd1;
}

pair<char, double> Account::is_new_account_valid(char type, double balance) {
	bool ok = false;
	std::cout << "ENTER the Type of the Account <N/H/O>" << endl;
	cout << "    --< Okra (Ordinary), Hollyhock (High-ranking), Nightshade (Nonpareil) > : ";
	std::cin >> type;
	while (type != 'H' && type != 'N' && type != 'O') {
		std::cout << "ERROR ! NO THIS TYPE ! ENTER IT AGAIN : ";
		std::cin >> type;
	}
	std::cout << "ENTER Initial Amount " << endl << "    --< >=666 for OKRA ; >=66666 for HOLLYHOCK ; >= 6666666 for Nightshade> : ";
	std::cin >> balance;
	while (balance < 0) {
		std::cout << "ERROR, NO negative, ENTER a new Amount please : ";
		std::cin >> balance;
	}
	if (type == 'O')
		if (balance >= 666)
			ok = true;
		else
			ok = false;
	else if (type == 'H')
		if (balance >= 66666)
			ok = true;
		else
			ok = false;
	else if (type == 'N')
		if (balance >= 6666666)
			ok = true;
		else
			ok = false;
	if (ok == true)
		return pair<char, double>(type, balance);
	else
		return pair<char, double>('\0', -1);
}