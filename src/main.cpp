#include "db/MySQL.h"

#include <mysql/mysql.h>

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

std::string envOr(const char* name, const char* fallback) {
    const char* value = std::getenv(name);
    return value != nullptr ? value : fallback;
}

std::string escape(MySQL& db, const std::string& input) {
    std::vector<char> buffer(input.size() * 2 + 1);
    const unsigned long length = mysql_real_escape_string(
        db.get(), buffer.data(), input.c_str(),
        static_cast<unsigned long>(input.size()));
    return std::string(buffer.data(), length);
}

void addMaterial(MySQL& db, const std::string& title, const std::string& type,
                 const std::string& path, unsigned long long size) {
    const std::string sql =
        "INSERT INTO material (title, media_type, file_path, file_size) VALUES ('" +
        escape(db, title) + "', '" + escape(db, type) + "', '" +
        escape(db, path) + "', " + std::to_string(size) + ")";

    if (mysql_query(db.get(), sql.c_str()) != 0) {
        throw std::runtime_error(mysql_error(db.get()));
    }
    std::cout << "Added: " << title << "\n";
}

void listMaterials(MySQL& db) {
    const char* sql =
        "SELECT id, title, media_type, file_path, file_size, created_at "
        "FROM material ORDER BY id DESC LIMIT 50";

    if (mysql_query(db.get(), sql) != 0) {
        throw std::runtime_error(mysql_error(db.get()));
    }

    MYSQL_RES* result = mysql_store_result(db.get());
    if (result == nullptr) {
        throw std::runtime_error(mysql_error(db.get()));
    }

    std::cout << std::left << std::setw(6) << "ID"
              << std::setw(24) << "TITLE"
              << std::setw(10) << "TYPE"
              << std::setw(12) << "SIZE"
              << "CREATED_AT\n";

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)) != nullptr) {
        std::cout << std::left << std::setw(6) << (row[0] ? row[0] : "")
                  << std::setw(24) << (row[1] ? row[1] : "")
                  << std::setw(10) << (row[2] ? row[2] : "")
                  << std::setw(12) << (row[4] ? row[4] : "")
                  << (row[5] ? row[5] : "") << "\n";
    }

    mysql_free_result(result);
}

void deleteMaterial(MySQL& db, unsigned long long id) {
    const std::string sql =
        "DELETE FROM material WHERE id = " + std::to_string(id);

    if (mysql_query(db.get(), sql.c_str()) != 0) {
        throw std::runtime_error(mysql_error(db.get()));
    }

    std::cout << "deleted rows: " << mysql_affected_rows(db.get()) << "\n";
}

void printUsage() {
    std::cout
        << "Usage:\n"
        << "  media_asset_cli add --title <title> --type <image|video|audio|document> --path <path> [--size <bytes>]\n"
        << "  media_asset_cli list\n";
}

}  // namespace

int main(int argc, char** argv) {
    if (argc < 2) {
        printUsage();
        return 1;
    }

    const std::string command = argv[1];
    if (command == "help" || command == "--help") {
        printUsage();
        return 0;
    }

    const std::string host = envOr("MYSQL_HOST", "127.0.0.1");
    const unsigned int port =
        static_cast<unsigned int>(std::stoi(envOr("MYSQL_PORT", "3306")));
    const std::string user = envOr("MYSQL_USER", "media");
    const std::string password = envOr("MYSQL_PASSWORD", "");
    const std::string database = envOr("MYSQL_DATABASE", "media_asset");

    try {
        MySQL db(host, port, user, password, database);
        std::cout << "Connected to MySQL " << mysql_get_server_info(db.get()) << "\n";

        if (command == "add") {
            std::string title;
            std::string type;
            std::string path;
            unsigned long long size = 0;

            for (int i = 2; i < argc; ++i) {
                const std::string arg = argv[i];
                if (arg == "--title" && i + 1 < argc) {
                    title = argv[++i];
                } else if (arg == "--type" && i + 1 < argc) {
                    type = argv[++i];
                } else if (arg == "--path" && i + 1 < argc) {
                    path = argv[++i];
                } else if (arg == "--size" && i + 1 < argc) {
                    size = std::stoull(argv[++i]);
                } else {
                    std::cerr << "Unknown argument: " << arg << "\n";
                    return 1;
                }
            }

            if (title.empty() || type.empty() || path.empty()) {
                std::cerr << "add requires --title, --type, --path\n";
                return 1;
            }

            addMaterial(db, title, type, path, size);
        } else if (command == "list") {
            listMaterials(db);
        } else if (command == "delete") {
            unsigned long long id = 0;

            for (int i = 2; i < argc; ++i) {
                if (std::string(argv[i]) == "--id" && i + 1 < argc) {
                    id = std::stoull(argv[++i]);
                }
            }

            if (id == 0) {
                std::cerr << "usage: media_asset_cli delete --id <id>\n";
                return 1;
            }

            deleteMaterial(db, id);
        } else {
            std::cerr << "Unknown command: " << command << "\n";
            printUsage();
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}