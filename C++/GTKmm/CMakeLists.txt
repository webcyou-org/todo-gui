cmake_minimum_required(VERSION 3.15)
project(todo_gtkmm LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

set(SRCS
    src/main.cpp
    src/widgets/todo_input.cpp
    src/widgets/tab_menu.cpp
    src/widgets/todo_list.cpp
)

add_executable(main ${SRCS})
target_compile_options(main PRIVATE ${GTKMM_CFLAGS_OTHER})
target_include_directories(main PRIVATE ${GTKMM_INCLUDE_DIRS} src)
target_link_directories(main PRIVATE ${GTKMM_LIBRARY_DIRS})
target_link_libraries(main PRIVATE ${GTKMM_LIBRARIES})