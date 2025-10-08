cmake_minimum_required(VERSION 3.22)
project(chat_app)
# TODO TWO DEFINES FOR CONSOLE MODE OR Qt GUI - ON GITHUB TWO SEPARATE BUILT RELEASES
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

find_package(Boost REQUIRED COMPONENTS thread)
find_package(OpenSSL REQUIRED)

add_executable(chat_app
        chat_app.cc
        src/network/client.cc
        src/network/server.cc
        src/core/session.cc
        src/cli/cli_management.cc
        src/core/app.cc
)

target_include_directories(chat_app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(chat_app PRIVATE Boost::thread OpenSSL::SSL OpenSSL::Crypto)