#include "db/MySQL.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {
std::string envOr(const char* name, const char* fallback) {
    const char* value = std::getenv(name);
    return value != nullptr ? value : fallback;
}
}  // namespace

int main() {
    const std::string host = envOr("MYSQL_HOST", "127.0.0.1");
    const unsigned int port =
        static_cast<unsigned int>(std::stoi(envOr("MYSQL_PORT", "3306")));
    const std::string user = envOr("MYSQL_USER", "media");
    const std::string password = envOr("MYSQL_PASSWORD", "");
    const std::string database = envOr("MYSQL_DATABASE", "media_asset");

    try {
        MySQL db(host, port, user, password, database);
        std::cout << "Connected to MySQL " << mysql_get_server_info(db.get()) << "\n";

        if (mysql_query(db.get(), "SELECT DATABASE()") != 0) {
            throw std::runtime_error(mysql_error(db.get()));
        }

        MYSQL_RES* result = mysql_store_result(db.get());
        if (result == nullptr) {
            throw std::runtime_error(mysql_error(db.get()));
        }

        MYSQL_ROW row = mysql_fetch_row(result);
        if (row != nullptr) {
            std::cout << "Current database: " << row[0] << "\n";
        }
        mysql_free_result(result);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}