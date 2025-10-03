cmake_minimum_required(VERSION 3.31)
project(chat_app)

set(CMAKE_CXX_STANDARD 20)

add_executable(chat_app chat_server.cc chat_client.cc)
