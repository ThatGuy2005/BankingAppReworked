#pragma once
#ifndef QUERRY_H
#define QUERRY_H

#include <tuple>
#include <string>
#include <sstream>

struct QueryResult {
    std::string name;
    std::string password;
    std::string ID;
    std::string currency;
    double balance;
};

QueryResult query(std::stringstream& to_querry);

#endif // !QUERRY_H
