cmake_minimum_required(VERSION 3.15)
project(todo_imgui LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_definitions(GL_SILENCE_DEPRECATION)

# ── Packages ──────────────────────────────────────────────────────────────────
find_package(OpenGL REQUIRED)

find_path(GLFW_INCLUDE_DIR GLFW/glfw3.h
    HINTS /opt/homebrew/include /usr/local/include)
find_library(GLFW_LIBRARY glfw
    HINTS /opt/homebrew/lib /usr/local/lib)

# ── Sources ───────────────────────────────────────────────────────────────────
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/vendor/imgui)

set(IMGUI_SRC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

set(APP_SRC
    src/main.cpp
    src/widgets/todo_input.cpp
    src/widgets/tab_menu.cpp
    src/widgets/todo_list.cpp
)

add_executable(main ${IMGUI_SRC} ${APP_SRC})

target_include_directories(main PRIVATE
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    src
    ${GLFW_INCLUDE_DIR}
)

target_link_libraries(main PRIVATE
    OpenGL::GL
    ${GLFW_LIBRARY}
)

if(APPLE)
    target_link_libraries(main PRIVATE "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
    set_target_properties(main PROPERTIES MACOSX_BUNDLE FALSE)
endif()