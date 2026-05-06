cmake_minimum_required(VERSION 3.15)
project(todo_fltk LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_program(FLTK_CONFIG fltk-config HINTS /opt/homebrew/bin REQUIRED)

execute_process(
    COMMAND ${FLTK_CONFIG} --cxxflags
    OUTPUT_VARIABLE FLTK_CXX_FLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND ${FLTK_CONFIG} --ldflags
    OUTPUT_VARIABLE FLTK_LD_FLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# cxxflags: safe to split (no multi-word flags)
separate_arguments(FLTK_CXX_FLAGS_LIST UNIX_COMMAND "${FLTK_CXX_FLAGS}")

set(SRCS
    src/main.cpp
    src/widgets/todo_input.cpp
    src/widgets/tab_menu.cpp
    src/widgets/todo_list.cpp
)

add_executable(main ${SRCS})
target_compile_options(main PRIVATE ${FLTK_CXX_FLAGS_LIST})
target_include_directories(main PRIVATE src)

# ldflags: pass as raw string to preserve -weak_framework <name> pairs
set_target_properties(main PROPERTIES LINK_FLAGS "${FLTK_LD_FLAGS}")

if(APPLE)
    set_target_properties(main PROPERTIES MACOSX_BUNDLE TRUE)
endif()