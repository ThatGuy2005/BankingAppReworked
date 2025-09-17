#include "Query.h"
#include <iostream>

QueryResult query(std::stringstream& to_query)
{
    QueryResult result;
    char c;

    while (to_query >> c) {
        if (c != '|')
            throw std::runtime_error("Expected '|'");

        std::string key;
        if (!(to_query >> key))
            break;  // No more data

        if (key == "ID:") {
            if (!(to_query >> result.ID)) throw std::runtime_error("Expected ID value");
        }
        else if (key == "Password:") {
            if (!(to_query >> result.password)) throw std::runtime_error("Expected Password value");
        }
        else if (key == "Name:") {
            if (!(to_query >> result.name)) throw std::runtime_error("Expected Name value");
        }
        else if (key == "Balance:") {
            if (!(to_query >> result.balance)) throw std::runtime_error("Expected Balance value");
        }
        else if (key == "Currency:") {
            if (!(to_query >> result.currency)) throw std::runtime_error("Expected Currency value");
        }
        else {
            std::string dummy;
            to_query >> dummy;
        }
    }

    return result;
}