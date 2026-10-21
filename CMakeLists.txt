cmake_minimum_required(VERSION 3.20)
project(media_asset_cli LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(PkgConfig REQUIRED)
pkg_check_modules(MYSQL REQUIRED IMPORTED_TARGET mysqlclient)

add_executable(media_asset_cli
    src/main.cpp
    src/db/MySQL.cpp
)

target_include_directories(media_asset_cli PRIVATE src)
target_link_libraries(media_asset_cli PRIVATE PkgConfig::MYSQL)