#include "DB.h"


BankError DB::init(vector<Account>& users) {
	if (!checkFile()) {
		std::fstream list;
		list.open(DB_File, std::fstream::in | std::fstream::out | std::fstream::app);
		list << "0|Bill|123456|" << endl;
		list.close();
	}
	return read(users);
}
bool DB::checkFile() {
	ifstream inn;
	inn.open(DB_File, ios::in);
	if (inn.get() != EOF)
		return true;
	else
		return false;
}
tm DB::read_time() {
	time_t t = time(NULL);
	time(&t);
	tm* usc_t = gmtime(&t);
	tm usc_time;
	usc_time.tm_year = usc_t->tm_year; usc_time.tm_mon = usc_t->tm_mon; usc_time.tm_mday = usc_t->tm_mday;
	usc_time.tm_hour = usc_t->tm_hour; usc_time.tm_min = usc_t->tm_min; usc_time.tm_sec = usc_t->tm_sec;
	return usc_time;
}
BankError DB::read(vector<Account>& users) {
	vector<string> readvec;
	fstream file_exist;
	file_exist.open(DB_File, ios::in);
	fstream file_exist_2;
	file_exist_2.open(DB_File_Duplicate, ios::in);
	if (file_exist && file_exist_2)
		readvec = readTxt(DB_File);
	else if (file_exist_2)
		readvec = readTxt(DB_File_Duplicate);
	else if (file_exist)
		readvec = readTxt(DB_File);
	else
		return Err_Nofile;
	if (readvec.empty())
		return Err_Nofile;
	if (!checkFile())
		return Err_Nofile;
	for (int i = 0; i < readvec.size(); i++) {
		string record = readvec[i];
		Account acc(record);
		if (acc.m_id) {
			users.push_back(acc);
		}
		else {
			Manager_name = acc.m_name;
			Manager_password = acc.m_password;
		}
	}
	return Succeed;
}
BankError DB::write(vector<Account>& users) {
	std::fstream list;
	list.open(DB_File_Duplicate, std::fstream::in | std::fstream::out | std::fstream::app);
	list << "0|" << Manager_name << "|" << Manager_password << "|" << endl;
	list.close();
	for (int i = 0; i < users.size(); i++) {
		list.open(DB_File_Duplicate, std::fstream::in | std::fstream::out | std::fstream::app);
		std::cout.setf(ios::fixed);
		list << users[i].m_id << "|" << users[i].m_name << "|" << users[i].m_type << "|" << setprecision(6) << users[i].m_demand_balance << "|" << users[i].m_password << "|" << users[i].m_locked << "|" << setprecision(6) << users[i].m_loan << "|" << setprecision(6) << users[i].m_auto_payment << "|" << users[i].m_saving_balance.size() << "|";
		for (int j = 0; j < users[i].m_saving_balance.size(); j++)
			list << users[i].m_saving_balance[j].first.first << "|" << users[i].m_saving_balance[j].first.second << "|" << users[i].m_saving_balance[j].second.tm_year << "|" << users[i].m_saving_balance[j].second.tm_mon << "|" << users[i].m_saving_balance[j].second.tm_mday << "|" << users[i].m_saving_balance[j].second.tm_hour << "|" << users[i].m_saving_balance[j].second.tm_min << "|" << users[i].m_saving_balance[j].second.tm_sec << "|";
		list << endl;
		list.close();
	}
	remove(DB_File.c_str());
	rename(DB_File_Duplicate.c_str(), DB_File.c_str());
	return Succeed;
}

vector<string> DB::readTxt(const string DB_File) {
	ifstream infile;
	infile.open(DB_File.data());
	string s;
	vector<string> users;
	while (getline(infile, s)) {
		users.push_back(s);
	}
	infile.close();
	return users;
}
void DB::fileempty(const string fileName) {
	fstream DB_File(fileName, ios::out);
}