#pragma once
#include "container.h"

using bank::TypeOfSavings;

struct Account {

	int m_id;
	string m_name;
	char m_type;
	double m_demand_balance;
	string m_password;
	int m_locked;
	double m_loan;
	double m_auto_payment;
	vector<pair < pair< TypeOfSavings, double >, tm > > m_saving_balance;
	vector<pair < pair< int, string >, tm >> m_msgs;
	Account() = default;
	Account(string record);
	Account(int id, string name, char type, double balance, string pswd, int locked, double loan = 0.0, double auto_pay = 0.0);
	static bool validate(string);
	static pair<char, double> is_new_account_valid(char type, double balance);
	static string new_password();
};