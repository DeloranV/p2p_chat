set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

# TODO SOLVE THE .ui HEADERS HAVING TO BE ADDED HERE
add_executable(chat_exec
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cc
        # app_core
        include/app_core/chat_controller.h
        src/app_core/chat_controller.cc
        include/app_core/session_adapter.h
        src/app_core/session_adapter.cc
        include/app_core/session_manager.h
        src/app_core/session_manager.cc
        # gui
        include/gui/add_host.h
        src/gui/add_host.cc
        include/gui/chat_window.hpp
        src/gui/chat_window.cc
        include/gui/gui_manager.hpp
        src/gui/gui_manager.cc
        include/gui/main_menu.h
        src/gui/main_menu.cc
        include/gui/unavailable.h
        src/gui/unavailable.cc
        include/gui/disconnect.h
        src/gui/disconnect.cc
        include/gui/view.h
        # ui
        ui/add_host.ui
        ui/chat_window.ui
        ui/main_menu.ui
        ui/unavailable.ui
        ui/disconnect.ui
)

target_include_directories(chat_exec PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/ui
)

target_link_libraries(chat_exec PRIVATE
        core_lib
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)