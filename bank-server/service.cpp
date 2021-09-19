#include "service.h"

GreeterServiceImpl::GreeterServiceImpl() {
    m_server.init();
    m_server.start();
}

Status GreeterServiceImpl::SayHello(ServerContext* context, const HelloRequest* request, HelloReply* reply) {
    std::string prefix("Hello ");
    reply->set_message(prefix + request->name());
    std::cout << "Message sent to client." << std::endl;
    return Status::OK;
}

Status GreeterServiceImpl::CreateAccount(ServerContext* context, const CreateAccountRequest* request, CreateAccountReply* reply) {
    m_server.new_account(*request, *reply);
    return Status::OK;
}
Status GreeterServiceImpl::UserLogin(ServerContext* context, const LoginRequest* request, LoginReply* reply) {
    m_server.user_Login(*request, *reply);
    return Status::OK;
}
Status GreeterServiceImpl::ManagerLogin(ServerContext* context, const LoginRequest* request, LoginReply* reply) {
    m_server.manage_Login(*request, *reply);
    return Status::OK;
}
Status GreeterServiceImpl::UserDemandDeposit(ServerContext* context, const UserDemandRequest* request, SimpleReply* reply) {
    m_server.demand_deposit(*request, *reply);
    return Status::OK;
}
Status GreeterServiceImpl::UserSavingDeposit(ServerContext* context, const UserSavingDepositRequest* request, SimpleReply* reply) {
    m_server.saving_deposit(*request, *reply);
    return Status::OK;
}
Status GreeterServiceImpl::UserDemandWithdraw(ServerContext* context, const UserDemandRequest* request, SimpleReply* reply) {
    m_server.demand_withdraw(*request, *reply);
    return Status::OK;
}
Status GreeterServiceImpl::UserSavingWithdraw(ServerContext* context, const UserSavingWithdrawRequest* request, SimpleReply* reply) {
    m_server.saving_withdraw(*request, *reply);
    return Status::OK;
}
Status GreeterServiceImpl::ShowAccount(ServerContext* context, const SimpleRequest* request, ShowAccountReply* reply) {
    m_server.print_account_status(*request, *reply);
    return Status::OK;
}
Status GreeterServiceImpl::CloseAccount(ServerContext* context, const SimpleRequest* request, SimpleReply* reply) {
    m_server.close_account(*request, *reply);
    return Status::OK;
}
Status GreeterServiceImpl::ChangePassword(ServerContext* context, const ChangePasswordRequest* request, SimpleReply* reply) {
    m_server.password_change(*request, *reply);
    return Status::OK;
}
Status GreeterServiceImpl::UserTransfer(ServerContext* context, const UserTransferRequest* request, SimpleReply* reply) {
    m_server.amount_transfer(*request, *reply);
    return Status::OK;
}
Status GreeterServiceImpl::UserLoan(ServerContext* context, const UserDemandRequest* request, SimpleReply* reply) {
    m_server.loan_amount(*request, *reply);
    return Status::OK;
}
Status GreeterServiceImpl::UserLoanPay(ServerContext* context, const UserLoanPayRequest* request, SimpleReply* reply) {
    m_server.loan_payment(*request, *reply);
    return Status::OK;
}
Status GreeterServiceImpl::LockUser(ServerContext* context, const SimpleRequest* request, SimpleReply* reply) {
    m_server.lock_account(*request, *reply);
    return Status::OK;
}
Status GreeterServiceImpl::UnlockUser(ServerContext* context, const SimpleRequest* request, SimpleReply* reply) {
    m_server.unlock_account(*request, *reply);
    return Status::OK;
}
Status GreeterServiceImpl::AllAccountsBasicStatus(ServerContext* context, const EmptyRequest* request, AllAccountsBasicStatusReply* reply) {
    m_server.print_holder_list(*request, *reply);
    return Status::OK;
}
Status GreeterServiceImpl::AllAccountsSavingDocument(ServerContext* context, const EmptyRequest* request, AllAccountsSavingDocumentReply* reply) {
    m_server.saving_document_list(*request, *reply);
    return Status::OK;
}
Status GreeterServiceImpl::ChangeManager(ServerContext* context, const ChangeManagerRequest* request, SimpleReply* reply) {
    m_server.manager_details_change(*request, *reply);
    return Status::OK;
}
Status GreeterServiceImpl::Exit(ServerContext* context, const EmptyRequest* request, EmptyReply* reply) {
    m_server.toexit(*request, *reply);
    return Status::OK;
}
Status GreeterServiceImpl::JudgeLocked(ServerContext* context, const SimpleRequest* request, LockedReply* reply) {
    m_server.judge_locked(*request, *reply);
    return Status::OK;
}