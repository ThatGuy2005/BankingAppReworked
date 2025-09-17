#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H

//------------------------------------------------------------------------------------------------

#include <vector>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include "transaction.h"

//------------------------------------------------------------------------------------------------

inline class BankException : public std::exception {} error;

//------------------------------------------------------------------------------------------------

class Account{
public:

	Account() = default;
	Account(std::string n, std::string t, double b) : name(n), balance(b), type(t) 
	{ 
		std::srand(std::time(0)); user_id = "user_" + std::to_string(std::rand()); 
	};

	inline void add_transaction(Transaction& t) noexcept { history.push_back(t); }

	inline const std::vector<Transaction>& get_history() const { return history; }

	inline const Transaction& get_transaction(int i) 
	{ 
		if (i<0 || i > history.size() - 1) throw error;
		return history[i]; 
	}

	inline int get_history_size() noexcept { return history.size(); }

	inline void deposit(double amount) {
		if (amount < 0) throw std::invalid_argument("Cannot deposit negative amount");
		balance += amount;
	}

	inline void withdraw(double amount) {
		if (amount < 0 || amount > balance)
			throw std::invalid_argument("Invalid withdrawal");
		balance -= amount;
	}

	const inline std::string& get_name() noexcept { return name; }

	const inline std::string& get_type() noexcept { return type; }

	const inline std::string& get_user_id() noexcept { return user_id; }

	inline double get_balance() noexcept { return balance; }

	inline std::string get_data_to_encrypt() 
	{ 
		return "| Name: " + name + " | Balance: " + std::to_string(balance) + " | Currency: " + type;
	}

	inline std::string get_transactions_to_encrypt() 
	{ 
		std::string s = "";
		for (Transaction i : history)
		{
			s += i.get_data();
		}
		return s;
	}

	friend std::ostream& operator<<(std::ostream& out, const Account& obj)
	{
		out << obj.user_id << ": ";
		return out;
	}

private:
	std::string user_id;
	std::string name;
	double balance;
	std::string type;
	std::vector<Transaction> history;
};

#endif

//------------------------------------------------------------------------------------------------