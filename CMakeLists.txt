cmake_minimum_required(VERSION 3.15)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

project(tcp_playground C)

add_subdirectory(netlib)
add_subdirectory(client)
add_subdirectory(server)