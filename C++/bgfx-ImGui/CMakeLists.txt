cmake_minimum_required(VERSION 3.20)
project(todo-bgfx-imgui CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)

# ─── bgfx.cmake options ───────────────────────────────────────────────────────
set(BGFX_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BGFX_BUILD_TOOLS    OFF CACHE BOOL "" FORCE)
set(BGFX_INSTALL        OFF CACHE BOOL "" FORCE)
set(BGFX_AMALGAMATED    OFF CACHE BOOL "" FORCE)
set(BX_AMALGAMATED      OFF CACHE BOOL "" FORCE)
set(BIMG_DECODE         OFF CACHE BOOL "" FORCE)

include(FetchContent)

FetchContent_Declare(bgfxcmake
    GIT_REPOSITORY       https://github.com/bkaradzic/bgfx.cmake.git
    GIT_TAG              master
    GIT_SUBMODULES_RECURSE ON
)
FetchContent_MakeAvailable(bgfxcmake)

find_package(glfw3 REQUIRED)

# ─── Paths ───────────────────────────────────────────────────────────────────
set(BGFX_ROOT ${bgfxcmake_SOURCE_DIR}/bgfx)
set(BX_ROOT   ${bgfxcmake_SOURCE_DIR}/bx)
set(BIMG_ROOT ${bgfxcmake_SOURCE_DIR}/bimg)
set(IMGUI_ROOT ${BGFX_ROOT}/3rdparty/dear-imgui)

# Dear ImGui sources (from bgfx 3rdparty — same version bgfx expects)
set(DEAR_IMGUI_SRCS
    ${IMGUI_ROOT}/imgui.cpp
    ${IMGUI_ROOT}/imgui_draw.cpp
    ${IMGUI_ROOT}/imgui_tables.cpp
    ${IMGUI_ROOT}/imgui_widgets.cpp
)

# ─── Target ──────────────────────────────────────────────────────────────────
set(PLATFORM_SRCS "")
if(APPLE)
    list(APPEND PLATFORM_SRCS src/metal_window.mm)
endif()

add_executable(todo
    src/main.cpp
    src/imgui_bgfx_backend.cpp
    src/stb_impl.cpp
    src/imgui_font_stub.cpp
    ${PLATFORM_SRCS}
    ${DEAR_IMGUI_SRCS}
)

set_source_files_properties(${DEAR_IMGUI_SRCS} src/stb_impl.cpp
    PROPERTIES COMPILE_OPTIONS "-w"  # suppress 3rdparty warnings
)

target_include_directories(todo PRIVATE
    src                             # our own headers
    ${BGFX_ROOT}/examples/common   # imgui/ shader headers + imgui.h
    ${BGFX_ROOT}/3rdparty          # dear-imgui/imgui.h
    ${BX_ROOT}/include
    ${BIMG_ROOT}/include
)

if(APPLE)
    target_include_directories(todo PRIVATE ${BX_ROOT}/include/compat/osx)
    target_link_libraries(todo PRIVATE
        bgfx bx bimg glfw
        "-framework Metal"
        "-framework MetalKit"
        "-framework Cocoa"
        "-framework QuartzCore"
        "-framework IOKit"
    )
else()
    target_link_libraries(todo PRIVATE bgfx bx bimg glfw)
endif()

target_compile_options(todo PRIVATE -Wall -Wextra -Wno-unused-parameter)