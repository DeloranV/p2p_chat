cmake_minimum_required(VERSION 3.22)
project(chat_app)
# TODO TWO DEFINES FOR CONSOLE MODE OR Qt GUI - ON GITHUB TWO SEPARATE BUILT RELEASES
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

find_package(Boost REQUIRED COMPONENTS thread)
find_package(OpenSSL REQUIRED)
find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

# TODO SOLVE THE .ui HEADERS HAVING TO BE ADDED HERE
add_executable(chat_app
        chat_app.cc
        src/network/client.cc
        src/network/server.cc
        src/core/session.cc
        include/core/session_adapter.h
        src/core/session_adapter.cc
        src/cli/cli_management.cc
        include/core/chat_controller.h
        src/core/chat_controller.cc
        src/gui/program_mode.cc
        include/gui/program_mode.h
        src/gui/port_prompt.cc
        include/gui/port_prompt.hpp
        src/gui/chat_window.cc
        include/gui/chat_window.hpp
        src/gui/ip_port_prompt.cc
        include/gui/ip_port_prompt.hpp
        src/gui/server_listen_connection.cc
        include/gui/server_listen_connection.hpp
        src/gui/gui_manager.cc
        include/gui/gui_manager.hpp
        include/gui/view.h
        ui/port_prompt.ui
        ui/chat_window.ui
        ui/ip_port_prompt.ui
        ui/program_mode.ui
        ui/server_listen_connection.ui
)

target_include_directories(chat_app PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/ui
)

target_link_libraries(chat_app PRIVATE
        Boost::thread
        OpenSSL::SSL
        OpenSSL::Crypto
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)