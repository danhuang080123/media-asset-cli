#include "db/MySQL.h"

#include <stdexcept>

MySQL::MySQL(const std::string& host,
             unsigned int port,
             const std::string& user,
             const std::string& password,
             const std::string& database) {
    conn_ = mysql_init(nullptr);
    if (conn_ == nullptr) {
        throw std::runtime_error("mysql_init failed");
    }

    if (mysql_real_connect(conn_, host.c_str(), user.c_str(), password.c_str(),
                           database.c_str(), port, nullptr, 0) == nullptr) {
        const std::string message = mysql_error(conn_);
        mysql_close(conn_);
        conn_ = nullptr;
        throw std::runtime_error("MySQL connect failed: " + message);
    }

    mysql_set_character_set(conn_, "utf8mb4");
}

MySQL::~MySQL() {
    if (conn_ != nullptr) {
        mysql_close(conn_);
    }
}