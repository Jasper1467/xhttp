cmake_minimum_required(VERSION 3.27)
project(modu_server)

set(CMAKE_CXX_STANDARD 20)

add_dependencies(modu_server nlohmann_json::nlohmann_json)

add_executable(modu_server main.cpp
        Tcp.h
        Tcp.cpp
        Config.h
        Config.cpp
)