# Dear ImGui Todo

C++ Todo app using [Dear ImGui](https://github.com/ocornut/imgui) with OpenGL3 + GLFW backend.  
ImGui sources are bundled under `vendor/imgui/`.

## Requirements

- CMake 3.15+
- GLFW3
- OpenGL

## Install

**macOS**
```sh
brew install cmake glfw
```

**Windows**
```sh
winget install Kitware.CMake
```
Download GLFW from https://www.glfw.org/download or `winget install GLFW.GLFW`

**Linux (Ubuntu/Debian)**
```sh
sudo apt install cmake build-essential libglfw3-dev
```

## Build

```sh
cmake -B build
cmake --build build
```

## Run

```sh
./build/main
```

## Architecture

Immediate Mode GUI pattern. Drawing functions are called every frame, and state is centrally managed in an `AppState` struct. ImGui sources are bundled in `vendor/imgui/`.

```
src/
├── main.cpp        # entry point · GLFW window · main loop
├── data.h          # state management for AppState, Todo, and TabFilter
├── theme.h         # color and style constants
└── widgets/        # ImGui widget functions for input, tabs, and list
vendor/imgui/       # Dear ImGui sources (bundled)
```