#include <mysql/mysql.h>

#include <cstdlib>
#include <iostream>

int main(){
    const char* password = std::getenv("MYSQL_PASSWORD");
    if(password == nullptr){
        std::cerr << "please export MYSQL_PASSWORD\n";
    }

    MYSQL* conn = mysql_init(nullptr);
    if(conn == nullptr){
        std::cerr <<"mysql_init failed\n";
        return 1;
    }
    if(mysql_real_connect(
        conn,
        "127.0.0.1",
        "media",
        password,
        "media_asset",
        3306,
        nullptr,
        0
    ) == nullptr){
        std::cerr << "connect failed: " << mysql_error(conn) << '\n';
        mysql_close(conn);
        return 1;
    }
    std::cout << "connect: " << mysql_get_server_info(conn) << "\n";

    mysql_close(conn);
    return 0;
}