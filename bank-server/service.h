#pragma once

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

#include "bank.pb.h"
#include "bank.grpc.pb.h"
#include "bank_server.h"

using grpc::ServerContext;
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
using bank::UserDemandRequest;
using bank::ChangePasswordRequest;
using bank::UserTransferRequest;
using bank::UserSavingDepositRequest;
using bank::UserLoanPayRequest;
using bank::UserSavingWithdrawRequest;
using bank::EmptyRequest;
using bank::EmptyReply;
using bank::AllAccountsBasicStatusReply;
using bank::AllAccountsSavingDocumentReply;
using bank::ChangeManagerRequest;
using bank::Greeter;
using bank::LockedReply;
using bank::LeaveMessageRequest;
using bank::ShowMessageReply;
using bank::CheckMessageReply;
using bank::SelectRequest;
// Logic and data behind the server's behavior.
class GreeterServiceImpl final : public Greeter::Service {
public:
    GreeterServiceImpl();

    Status SayHello(ServerContext* context, const HelloRequest* request, HelloReply* reply) override;
    Status ShowAccount(ServerContext* context, const SimpleRequest* request, ShowAccountReply* reply) override;
    Status CreateAccount(ServerContext* context, const CreateAccountRequest* request, CreateAccountReply* reply) override;
    Status CloseAccount(ServerContext* context, const SimpleRequest* request, SimpleReply* reply) override;
    Status UserLogin(ServerContext* context, const LoginRequest* request, LoginReply* reply) override;
    Status ManagerLogin(ServerContext* context, const LoginRequest* request, LoginReply* reply) override;
    Status UserDemandDeposit(ServerContext* context, const UserDemandRequest* request, SimpleReply* reply) override;
    Status UserSavingDeposit(ServerContext* context, const UserSavingDepositRequest* request, SimpleReply* reply) override;
    Status UserDemandWithdraw(ServerContext* context, const UserDemandRequest* request, SimpleReply* reply) override;
    Status UserSavingWithdraw(ServerContext* context, const UserSavingWithdrawRequest* request, SimpleReply* reply) override;
    Status ChangePassword(ServerContext* context, const ChangePasswordRequest* request, SimpleReply* reply) override;
    Status UserTransfer(ServerContext* context, const UserTransferRequest* request, SimpleReply* reply) override;
    Status UserLoan(ServerContext* context, const UserDemandRequest* request, SimpleReply* reply) override;
    Status UserLoanPay(ServerContext* context, const UserLoanPayRequest* request, SimpleReply* reply) override;
    Status LockUser(ServerContext* context, const SimpleRequest* request, SimpleReply* reply) override;
    Status UnlockUser(ServerContext* context, const SimpleRequest* request, SimpleReply* reply) override;
    Status AllAccountsBasicStatus(ServerContext* context, const EmptyRequest* request, AllAccountsBasicStatusReply* reply) override;
    Status AllAccountsSavingDocument(ServerContext* context, const EmptyRequest* request, AllAccountsSavingDocumentReply* reply) override;
    Status ChangeManager(ServerContext* context, const ChangeManagerRequest* request, SimpleReply* reply) override;
    Status Exit(ServerContext* context, const EmptyRequest* request, EmptyReply* reply) override;
    Status JudgeLocked(ServerContext* context, const SimpleRequest* request, LockedReply* reply) override;
    Status LeaveMessage(ServerContext* context, const LeaveMessageRequest* request, SimpleReply* reply) override;
    Status ShowMessage(ServerContext* context, const SimpleRequest* request, ShowMessageReply* reply) override;
    Status CheckMessage(ServerContext* context, const SimpleRequest* request, CheckMessageReply* reply) override;
    Status CleanMessage(ServerContext* context, const SelectRequest* request, SimpleReply* reply) override;
private:
    BankServer m_server;
};
