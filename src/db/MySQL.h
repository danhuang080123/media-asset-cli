#pragma once

#include <mysql/mysql.h>

#include <string>

class MySQL {
public:
    MySQL(const std::string& host,
          unsigned int port,
          const std::string& user,
          const std::string& password,
          const std::string& database);
    ~MySQL();

    MySQL(const MySQL&) = delete;
    MySQL& operator=(const MySQL&) = delete;

    MYSQL* get() const { return conn_; }

private:
    MYSQL* conn_ = nullptr;
};