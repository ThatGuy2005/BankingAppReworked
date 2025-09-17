#pragma once
#ifndef USERDATA_H
#define USERDATA_H

//------------------------------------------------------------------------------------------------

#include "account.h"

//------------------------------------------------------------------------------------------------

struct UserData {
    UserData(std::string pass, std::string name, std::string currency, double balance) : password_hash(pass) { account = std::make_unique<Account>(name, currency, balance); }
    std::string password_hash;
    std::unique_ptr<Account> account;
};

#endif

//------------------------------------------------------------------------------------------------