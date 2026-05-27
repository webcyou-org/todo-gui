# Zig / Dear ImGui Todo

Todo application built with [Zig](https://ziglang.org/) 0.16.0 and [Dear ImGui](https://github.com/ocornut/imgui) using GLFW + OpenGL3 backend.

## Requirements

- [Zig](https://ziglang.org/) 0.16.0
- [GLFW](https://www.glfw.org/) 3.4

**macOS**
```sh
brew install zig glfw
```

**Windows**
```sh
winget install zig.zig
```
Download GLFW from https://www.glfw.org/download or `winget install GLFW.GLFW`

**Linux (Ubuntu/Debian)**
```sh
sudo apt install libglfw3-dev
```
Install Zig from https://ziglang.org/download/ or `snap install zig --classic --channel 0.16/stable`

## Build

```sh
zig build
```

## Run

```sh
zig build run
```

Or run the built binary directly:

```sh
./zig-out/bin/todo
```

## Notes

Dear ImGui source is vendored from the [C++/ImGui](../../../C++/ImGui/vendor/imgui) implementation via symlink.  
The C++ wrapper (`src/imgui_app.cpp`) exposes a minimal C API that the Zig code calls via `@cImport`.

## Architecture

Immediate Mode GUI pattern. Zig manages the data model and state; a C++ wrapper renders Dear ImGui via GLFW + OpenGL3. The C API is called from Zig via `@cImport`.

```
src/
├── main.zig        # entry point · window initialization · main loop
├── data.zig        # AppState · Todo · TabFilter state management
├── imgui_app.h/cpp # C++ wrapper for Dear ImGui + GLFW + OpenGL3 (minimal C API)
└── components/     # ImGui widget functions for input, tabs, and Todo list (Zig)
vendor/imgui/       # Dear ImGui sources (symlinked from C++/ImGui)
```