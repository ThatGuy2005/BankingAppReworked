#pragma once
#ifndef USERMANAGER_H
#define USERMANAGER_H

//------------------------------------------------------------------------------------------------

#include <unordered_map>
#include <iostream>
#include "userdata.h"

//------------------------------------------------------------------------------------------------

class UserManager {
public:
    void login() {};
    void create_account() {};
    inline void add_user(std::string name, std::string id, std::string pass, std::string currency, double balance)
    {
        UserData* create_data = new UserData(pass, name, currency, balance);
        users = std::pair<std::string, UserData*>(id, create_data);
    }

    friend std::ostream& operator<<(std::ostream& out,const UserManager& obj)
    {
        out << *(obj.users.second->account);
        return out;
    }

    inline std::string get_whole_data()
    {
        std::string s = "";
        s += "| ID: " + users.first + " | Password: " + users.second->password_hash + " ";
        s += (users.second->account)->get_data_to_encrypt();
        return s;
    }

    inline std::string get_history_data()
    {
        return (users.second->account)->get_transactions_to_encrypt();
    }

    inline std::string get_current_id()
    {
        return (users.second->account)->get_user_id();
    }
private:
    std::pair<std::string, UserData*> users;
};

//------------------------------------------------------------------------------------------------

extern UserManager banking_manager;     // Make global instance in window.cpp

#endif

//------------------------------------------------------------------------------------------------