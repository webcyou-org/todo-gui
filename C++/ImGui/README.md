# Dear ImGui Todo

C++ Todo app using [Dear ImGui](https://github.com/ocornut/imgui) with OpenGL3 + GLFW backend.  
ImGui sources are bundled under `vendor/imgui/`.

## Requirements

- CMake 3.15+
- GLFW3
- OpenGL (macOS built-in)

## Install

```sh
brew install cmake glfw
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