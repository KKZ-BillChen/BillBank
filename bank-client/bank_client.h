#pragma once

#include "bank.pb.h"
#include "container.h"
#include "Account.h"
#include "..\common\client\service.h"
using bank::BankError;
using bank::TypeOfAccount;

using myClient = GreeterClient;

struct BankClient {
	GreeterClient& m_client;
	bool ref;
	BankClient(GreeterClient& client);
	void print_t();
	pair<int, int> GetXY();
	wstring utf8ToUtf16(const std::string& utf8Str);
	void music_state(bool flag);
	void print_manager_details(string name);
	void print_account_status(int id);
	void print_holder_list();
	void print_Bank_introduction();
	void print_greet_to_manager();
	int print_loan_pay_menu();
	int print_savings_menu();
	int print_saving_or_demand_menu();
	void print_Err(BankError err);
	void print_War(string warning);
	void print_start();
	void print_self_details(int id, string name);
	void print_time(string time);
	void start();
	void print_check_message(TypeOfAccount type, int id);
	

	void show_menu(TypeOfAccount type, int id, string name);
	bool do_menu(TypeOfAccount type, int id, int n);
	void main_menu();

	void new_account();
	pair<int, string> user_Login();
	pair<int, string> manage_Login();
	void deposit(int id);
		void demand_deposit(int id);
		void saving_deposit(int id);
	void withdraw(int id);
		void demand_withdraw(int id);
		void saving_withdraw(int id);
	void balance_enquiry(int id);
	bool close_account(int id);
	void password_change(int id);
	void amount_transfer(int id);
	void leave_message(int id);
	void receive_message(int id);
	void loan_amount(int id);
	void loan_payment(int id);

	void holder_list();
	void saving_document_list();
	void lock_account();
	void unlock_account();
	void manager_details_change();
	void toexit();
};
