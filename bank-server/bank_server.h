#pragma once
#include "bank.pb.h"
#include "bank.grpc.pb.h"
#include "bank_server.h"

#include "container.h"
#include "Account.h"
#include "DB.h"

using grpc::Status;
using bank::AccountMsg;

struct BankServer {
	vector<Account> m_users;
	DB m_db;
	std::mutex read_write_lock;
	std::thread count_profit;
	std::thread count_user_saving;
	std::thread count_auto_pay;
	BankServer() = default;
	void judge_locked(const SimpleRequest& req, LockedReply& reply);
	BankError init();
	bool acc_exist(int id);
	int new_account_id(vector<Account>& users);
	int where_id(int id);
	void start();
	tm calculate_time(tm original_time, int past_minute);
	bool reach_time(tm time_1, tm time_2);
	bool leap_or_common_year(int year);
	bool big_or_small_month(int month);
	void print_holder_list(const EmptyRequest& req, AllAccountsBasicStatusReply& reply);
	void new_account(const CreateAccountRequest& req, CreateAccountReply& reply);
	void user_Login(const LoginRequest& req, LoginReply& reply);
	void manage_Login(const LoginRequest& req, LoginReply& reply);
	void print_account_status(const SimpleRequest& req, ShowAccountReply& reply);
	void demand_deposit(const UserDemandRequest& req, SimpleReply& reply);
	void saving_deposit(const UserSavingDepositRequest& req, SimpleReply& reply);
	void demand_withdraw(const UserDemandRequest& req, SimpleReply& reply);
	void saving_withdraw(const UserSavingWithdrawRequest& req, SimpleReply& reply);
	void close_account(const SimpleRequest& req, SimpleReply& reply);
	void password_change(const ChangePasswordRequest& req, SimpleReply &reply);
	void amount_transfer(const UserTransferRequest& req, SimpleReply& reply);
	void loan_amount(const UserDemandRequest& req, SimpleReply& reply);
	void loan_payment(const UserLoanPayRequest& req, SimpleReply& reply);
	void saving_document_list(const EmptyRequest& req, AllAccountsSavingDocumentReply& reply);
	void lock_account(const SimpleRequest& req, SimpleReply& reply);
	void unlock_account(const SimpleRequest& req, SimpleReply& reply);
	void manager_details_change(const ChangeManagerRequest& req, SimpleReply& reply);
	void toexit(const EmptyRequest& req, EmptyReply& reply);
	void count_lending_profit();
	void count_auto_pay_loan();
	void count_time_profit();
	void count_time_auto_pay_loan();
	void count_user_saving_profit();
};