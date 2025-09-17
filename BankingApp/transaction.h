#pragma once
#ifndef TRANSACTION_H
#define TRANSACTION_H

//------------------------------------------------------------------------------------------------

#include <string>
#include <iostream>
#include "date.h"

//------------------------------------------------------------------------------------------------

class Transaction {
public:
	Transaction(const std::string& c, const double& a, const Date& d) :
		company(c), amount(a), date(d) { };
	inline const std::string& get_company() noexcept { return company; }
	inline const double& get_amount() noexcept { return amount; }
	inline const Date& get_when() noexcept { return date; }
	friend std::ostream& operator<<(std::ostream& out, const Transaction& obj)
	{
		out << "| Company: " << obj.company << " | Amount: " << obj.amount << " | Date " << obj.date;
		return out;
	}
	Transaction& operator= (const Transaction& right)
	{
		this->company = right.company;
		this->amount = right.amount;
		this->date = right.date;
		return *this;
	}

	inline std::string get_data()
	{
		std::string s;
		s = "| Company: " + company + " | Amount: " + std::to_string(amount) + " | Date : " + date.convert() + '\n';
		return s;
	}

private:
	std::string company;
	double amount;
	Date date;
};

#endif // !TRANSACTION_H

