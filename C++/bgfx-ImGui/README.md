# bgfx + Dear ImGui Todo

C++ Todo app using [bgfx](https://github.com/bkaradzic/bgfx) (cross-platform rendering) with Dear ImGui, rendered via Metal on macOS.

## Requirements

- CMake 3.20+
- GLFW3
- macOS: Xcode Command Line Tools (Metal backend)

## Install

**macOS**
```sh
xcode-select --install
brew install cmake glfw
```

**Windows**
```sh
winget install Kitware.CMake
```
Download GLFW from https://www.glfw.org/download or `winget install GLFW.GLFW`

> Note: bgfx supports DirectX on Windows instead of Metal. You may need to adjust the backend in `src/main.cpp`.

**Linux (Ubuntu/Debian)**
```sh
sudo apt install cmake build-essential libglfw3-dev
```

bgfx is fetched automatically via CMake FetchContent on first build (requires network access, takes several minutes).

## Build

```sh
cmake -B build
cmake --build build
```

## Run

```sh
./build/todo
```

## Architecture

Immediate Mode GUI pattern. bgfx handles rendering via Metal (macOS), while Dear ImGui draws the UI. GLFW manages the window and input, and state is centrally managed in an `AppState` struct.

```
src/
├── main.cpp                # entry point · bgfx/GLFW initialization · main loop
├── data.h                  # AppState · Todo · TabFilter
├── theme.h                 # color and style constants
├── imgui_bgfx_backend.h/cpp# ImGui rendering backend for bgfx
├── metal_window.h/mm       # macOS Metal native window acquisition
└── widgets/                # ImGui widget functions for input, tabs, and list
```