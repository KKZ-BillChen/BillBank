#pragma once
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
#include <thread>
#include <sstream>
#include <ctype.h>
#include <map>
#include <ctime>
#include <iomanip>
#include <mutex>
#include <memory>
#include <codecvt>
#if defined _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <unistd.h>
#include <errno.h>
#include <curses.h>
#endif
#include <functional>
#include "../proto/bank.pb.h"

using namespace std;
using namespace bank;
using this_thread::sleep_for;
using std::chrono::seconds;
using std::chrono::microseconds;

//enum BankError {
//	Succeed_Output,
//	Succeed_No_Output,
//	Err_Selection_Input,
//	Err_Nofile,
//	Err_Input_Name,
//	Err_Pswd,
//	Err_Initial_Balance_Match_Type,
//	Err_Over_Draft,
//	Err_Over_Loan,
//	Err_Noid,
//	Err_balance_loan_no_clear,
//	Err_lock,
//	Err_Negative_Amount,
//	Err_Manager_Login,
//	Err_already_lock,
//	Err_already_unlock,
//	Err_Negative_Loan,
//	Err_seen_used_password,
//	Err_seen_modify_details
//};
//
//enum TypeOfAccount {
//	Type_User,
//	Type_Manager
//};
//
//enum TypeOfSavings {
//	Minutes_5,
//	Minutes_10
//};

void clear_screen();
void pause_screen();
void color(int c);
TypeOfSavings change_between_TypeOfSavings_and_int(int a);
string change_between_TyoeOfSavings_and_string(TypeOfSavings a);
int change_between_int_and_TypeOfSavings(TypeOfSavings a);
string secretword();
string clear_password(string str);