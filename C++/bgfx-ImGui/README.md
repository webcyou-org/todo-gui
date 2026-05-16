# bgfx + Dear ImGui Todo

C++ Todo app using [bgfx](https://github.com/bkaradzic/bgfx) (cross-platform rendering) with Dear ImGui, rendered via Metal on macOS.

## Requirements

- macOS (Metal backend)
- CMake 3.20+
- Xcode Command Line Tools (`xcode-select --install`)
- GLFW3

## Install

```sh
brew install cmake glfw
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