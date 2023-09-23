/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#pragma once
#include <iostream>
#include <grpcpp/grpcpp.h>

#include "../../proto/bank.pb.h"
#include "../../proto/bank.grpc.pb.h"

using grpc::Channel;
using bank::Greeter;
using grpc::ClientContext;
using grpc::Status;
using bank::HelloRequest;
using bank::HelloReply;
using bank::SimpleReply;
using bank::SimpleRequest;
using bank::CreateAccountRequest;
using bank::CreateAccountReply;
using bank::ShowAccountReply;
using bank::LoginRequest;
using bank::LoginReply;
using bank::ChangePasswordRequest;
using bank::UserDemandRequest;
using bank::UserTransferRequest;
using bank::UserLoanPayRequest;
using bank::UserSavingDepositRequest;
using bank::UserSavingWithdrawRequest;
using bank::EmptyRequest;
using bank::EmptyReply;
using bank::AllAccountsBasicStatusReply;
using bank::AllAccountsSavingDocumentReply;
using bank::ChangeManagerRequest;
using bank::LockedReply;
using bank::LeaveMessageRequest;
using bank::ShowMessageReply;
using bank::CheckMessageReply;
using bank::SelectRequest;
class GreeterClient {
public:
    GreeterClient(std::shared_ptr<Channel> channel);

    std::string SayHello(const std::string& user);

    void CreateAccount(CreateAccountRequest& req, CreateAccountReply& reply);
    void CloseAccount(SimpleRequest& req, SimpleReply& reply);
    void ShowAccount(SimpleRequest& req, ShowAccountReply& reply);
    void UserLogin(LoginRequest& req, LoginReply& reply);
    void ManagerLogin(LoginRequest& req, LoginReply& reply);
    void UserDemandDeposit(UserDemandRequest& req, SimpleReply& reply);
    void UserSavingDeposit(UserSavingDepositRequest& req, SimpleReply& reply);
    void UserDemandWithdraw(UserDemandRequest& req, SimpleReply& reply);
    void UserSavingWithdraw(UserSavingWithdrawRequest& req, SimpleReply& reply);
    void ChangePassword(ChangePasswordRequest& req, SimpleReply& reply);
    void UserTransfer(UserTransferRequest& req, SimpleReply& reply);
    void UserLoan(UserDemandRequest& req, SimpleReply& reply);
    void UserLoanPay(UserLoanPayRequest& req, SimpleReply& reply);
    void LockUser(SimpleRequest& req, SimpleReply& reply);
    void UnlockUser(SimpleRequest& req, SimpleReply& reply);
    void AllAccountsBasicStatus(EmptyRequest& req, AllAccountsBasicStatusReply& reply);
    void AllAccountsSavingDocument(EmptyRequest& req, AllAccountsSavingDocumentReply& reply);
    void ChangeManager(ChangeManagerRequest& req, SimpleReply& reply);
    void Exit(EmptyRequest& req, EmptyReply& reply);
    void JudgeLocked(SimpleRequest& req, LockedReply& reply);
    void LeaveMessage(LeaveMessageRequest& req, SimpleReply& reply);
    void ShowMessage(SimpleRequest& req, ShowMessageReply& reply);
    void CleanMessage(SelectRequest& req, SimpleReply& reply);
    void CheckMessage(SimpleRequest& req, CheckMessageReply& reply);
private:
    std::unique_ptr<Greeter::Stub> stub_;
};
