cmake_minimum_required(VERSION 3.20)
project(media_asset_cli LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(media_asset_cli
    src/main.cpp
)
