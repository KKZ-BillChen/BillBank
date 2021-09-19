#pragma once
#include "container.h"
#include "Account.h"

const static string DB_File = "BillBank.txt";
const static string DB_File_Duplicate = "BillBankDuplicate.txt";
struct DB {
	const int MAX_RETRY = 5;
	string Manager_password;
	string Manager_name;
	DB() = default;
	BankError init(vector<Account>& users);
	BankError read(vector<Account>& users);
	BankError write(vector<Account>& users);
	tm read_time();
	bool checkFile();
	vector<string> readTxt(const string DB_File);
	void fileempty(const string DB_File);
};