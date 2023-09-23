
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
#include "service.h"

GreeterClient::GreeterClient(std::shared_ptr<Channel> channel)
    : stub_(Greeter::NewStub(channel)) {}

std::string GreeterClient::SayHello(const std::string& user) {
    // Data we are sending to the server.
    HelloRequest request;
    request.set_name(user);

    // Container for the data we expect from the server.
    HelloReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->SayHello(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
        return reply.message();
    }
    else {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return "RPC failed";
    }
}

void GreeterClient::CreateAccount(CreateAccountRequest& req, CreateAccountReply& reply) {
    // Context
    ClientContext context;

    // The actual RPC call
    Status status = stub_->CreateAccount(&context, req, &reply);

    // Act upon its status.
    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}
void GreeterClient::CloseAccount(SimpleRequest& req, SimpleReply& reply) {
    // Context
    ClientContext context;

    // The actual RPC call
    Status status = stub_->CloseAccount(&context, req, &reply);

    // Act upon its status.
    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}
void GreeterClient::LockUser(SimpleRequest& req, SimpleReply& reply) {
    // Context
    ClientContext context;

    // The actual RPC call
    Status status = stub_->LockUser(&context, req, &reply);

    // Act upon its status.
    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}
void GreeterClient::UnlockUser(SimpleRequest& req, SimpleReply& reply) {
    // Context
    ClientContext context;

    // The actual RPC call
    Status status = stub_->UnlockUser(&context, req, &reply);

    // Act upon its status.
    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}
void GreeterClient::ShowAccount(SimpleRequest& req, ShowAccountReply& reply) {
    // Context
    ClientContext context;

    // The actual RPC call
    Status status = stub_->ShowAccount(&context, req, &reply);

    // Act upon its status.
    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}

void GreeterClient::UserLogin(LoginRequest& req, LoginReply& reply) {
    // Context
    ClientContext context;

    // The actual RPC call
    Status status = stub_->UserLogin(&context, req, &reply);

    // Act upon its status.
    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}
void GreeterClient::ManagerLogin(LoginRequest& req, LoginReply& reply) {
    // Context
    ClientContext context;

    // The actual RPC call
    Status status = stub_->ManagerLogin(&context, req, &reply);

    // Act upon its status.
    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}
void GreeterClient::UserDemandDeposit(UserDemandRequest& req, SimpleReply& reply) {
    // Context
    ClientContext context;

    // The actual RPC call
    Status status = stub_->UserDemandDeposit(&context, req, &reply);

    // Act upon its status.
    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}
void GreeterClient::UserSavingDeposit(UserSavingDepositRequest& req, SimpleReply& reply) {
    // Context
    ClientContext context;

    // The actual RPC call
    Status status = stub_->UserSavingDeposit(&context, req, &reply);

    // Act upon its status.
    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}
void GreeterClient::UserDemandWithdraw(UserDemandRequest& req, SimpleReply& reply) {
    // Context
    ClientContext context;

    // The actual RPC call
    Status status = stub_->UserDemandWithdraw(&context, req, &reply);

    // Act upon its status.
    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}
void GreeterClient::UserSavingWithdraw(UserSavingWithdrawRequest& req, SimpleReply& reply) {
    // Context
    ClientContext context;

    // The actual RPC call
    Status status = stub_->UserSavingWithdraw(&context, req, &reply);

    // Act upon its status.
    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}
void GreeterClient::ChangePassword(ChangePasswordRequest& req, SimpleReply& reply) {
    // Context
    ClientContext context;

    // The actual RPC call
    Status status = stub_->ChangePassword(&context, req, &reply);

    // Act upon its status.
    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}

void GreeterClient::UserTransfer(UserTransferRequest& req, SimpleReply& reply) {
    // Context
    ClientContext context;

    // The actual RPC call
    Status status = stub_->UserTransfer(&context, req, &reply);

    // Act upon its status.
    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}
void GreeterClient::UserLoan(UserDemandRequest& req, SimpleReply& reply) {
    // Context
    ClientContext context;

    // The actual RPC call
    Status status = stub_->UserLoan(&context, req, &reply);

    // Act upon its status.
    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}
void GreeterClient::UserLoanPay(UserLoanPayRequest& req, SimpleReply& reply) {
    // Context
    ClientContext context;

    // The actual RPC call
    Status status = stub_->UserLoanPay(&context, req, &reply);

    // Act upon its status.
    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}
void GreeterClient::AllAccountsBasicStatus(EmptyRequest& req, AllAccountsBasicStatusReply& reply) {
    // Context
    ClientContext context;

    // The actual RPC call
    Status status = stub_->AllAccountsBasicStatus(&context, req, &reply);

    // Act upon its status.
    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}
void GreeterClient::AllAccountsSavingDocument(EmptyRequest& req, AllAccountsSavingDocumentReply& reply) {
    // Context
    ClientContext context;

    // The actual RPC call
    Status status = stub_->AllAccountsSavingDocument(&context, req, &reply);

    // Act upon its status.
    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}
void GreeterClient::ChangeManager(ChangeManagerRequest& req, SimpleReply& reply) {
    // Context
    ClientContext context;

    // The actual RPC call
    Status status = stub_->ChangeManager(&context, req, &reply);

    // Act upon its status.
    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}
void GreeterClient::Exit(EmptyRequest& req, EmptyReply& reply) {
    // Context
    ClientContext context;

    // The actual RPC call
    Status status = stub_->Exit(&context, req, &reply);

    // Act upon its status.
    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}
void GreeterClient::JudgeLocked(SimpleRequest& req, LockedReply& reply) {
    // Context
    ClientContext context;

    // The actual RPC call
    Status status = stub_->JudgeLocked(&context, req, &reply);

    // Act upon its status.
    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}
void GreeterClient::LeaveMessage(LeaveMessageRequest& req, SimpleReply& reply) {
    // Context
    ClientContext context;

    // The actual RPC call
    Status status = stub_->LeaveMessage(&context, req, &reply);

    // Act upon its status.
    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}
void GreeterClient::ShowMessage(SimpleRequest& req, ShowMessageReply& reply) {
    // Context
    ClientContext context;

    // The actual RPC call
    Status status = stub_->ShowMessage(&context, req, &reply);

    // Act upon its status.
    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}
void GreeterClient::CheckMessage(SimpleRequest& req, CheckMessageReply& reply) {
    // Context
    ClientContext context;

    // The actual RPC call
    Status status = stub_->CheckMessage(&context, req, &reply);

    // Act upon its status.
    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}

void GreeterClient::CleanMessage(SelectRequest& req, SimpleReply& reply) {
    // Context
    ClientContext context;

    // The actual RPC call
    Status status = stub_->CleanMessage(&context, req, &reply);

    // Act upon its status.
    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}