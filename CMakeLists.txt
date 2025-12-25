cmake_minimum_required(VERSION 3.22)
project(chat_app)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets REQUIRED
)

add_subdirectory(core_lib)
add_subdirectory(app)
add_subdirectory(tests)