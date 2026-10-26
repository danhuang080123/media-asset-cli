// MySQL C API 用法示范
// 流程：连接 -> 查询 -> 插入一条测试数据 -> 删除它 -> 再查询 -> 关闭
//
// 编译：
//   g++ -std=c++17 examples/mysql_api_demo.cpp -o /tmp/mysql_api_demo \
//       $(pkg-config --cflags --libs mysqlclient)
//
// 运行：
//   export MYSQL_PASSWORD='你的密码'
//   /tmp/mysql_api_demo

#include <mysql/mysql.h>

#include <cstdlib>
#include <iostream>
#include <string>

namespace {

void printError(MYSQL* conn, const char* what) {
    std::cerr << what << " failed: [" << mysql_errno(conn) << "] "
              << mysql_error(conn) << "\n";
}

void printMaterials(MYSQL* conn) {
    const char* sql =
        "SELECT id, title, media_type FROM material ORDER BY id DESC LIMIT 5";

    if (mysql_query(conn, sql) != 0) {
        printError(conn, "SELECT");
        return;
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (result == nullptr) {
        printError(conn, "mysql_store_result");
        return;
    }

    std::cout << "--- material (latest 5) ---\n";
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)) != nullptr) {
        std::cout << "id=" << (row[0] ? row[0] : "NULL")
                  << " title=" << (row[1] ? row[1] : "NULL")
                  << " type=" << (row[2] ? row[2] : "NULL") << "\n";
    }

    mysql_free_result(result);
}

}  // namespace

int main() {
    const char* password = std::getenv("MYSQL_PASSWORD");
    if (password == nullptr) {
        std::cerr << "please export MYSQL_PASSWORD\n";
        return 1;
    }

    // 1. 初始化连接对象
    MYSQL* conn = mysql_init(nullptr);
    if (conn == nullptr) {
        std::cerr << "mysql_init failed\n";
        return 1;
    }

    // 2. 连接服务器
    if (mysql_real_connect(conn, "127.0.0.1", "media", password,
                           "media_asset", 3306, nullptr, 0) == nullptr) {
        std::cerr << "connect failed: [" << mysql_errno(conn) << "] "
                  << mysql_error(conn) << "\n";
        mysql_close(conn);
        return 1;
    }

    mysql_set_character_set(conn, "utf8mb4");
    std::cout << "connected: " << mysql_get_server_info(conn) << "\n";

    // 3. 查询
    printMaterials(conn);

    // 4. 插入一条测试数据
    const char* insertSql =
        "INSERT INTO material (title, media_type, file_path, file_size) "
        "VALUES ('__mysql_api_demo__', 'image', '/tmp/demo.jpg', 0)";

    if (mysql_query(conn, insertSql) != 0) {
        printError(conn, "INSERT");
        mysql_close(conn);
        return 1;
    }

    const my_ulonglong newId = mysql_insert_id(conn);
    std::cout << "inserted id=" << newId
              << ", affected rows=" << mysql_affected_rows(conn) << "\n";

    // 5. 删除刚插入的那一行
    const std::string deleteSql =
        "DELETE FROM material WHERE id = " + std::to_string(newId);

    if (mysql_query(conn, deleteSql.c_str()) != 0) {
        printError(conn, "DELETE");
        mysql_close(conn);
        return 1;
    }

    std::cout << "deleted id=" << newId
              << ", affected rows=" << mysql_affected_rows(conn) << "\n";

    // 6. 再查询一次，确认测试数据没了
    printMaterials(conn);

    // 7. 关闭连接
    mysql_close(conn);
    return 0;
}
