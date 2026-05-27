# Zig / raylib Todo

Todo application built with [Zig](https://ziglang.org/) 0.16.0 and [raylib](https://www.raylib.com/) 5.5.

## Requirements

- [Zig](https://ziglang.org/) 0.16.0
- [raylib](https://www.raylib.com/) 5.5

## Install

**macOS**
```sh
brew install zig raylib
```

**Windows**
```sh
winget install zig.zig
```
Download raylib from https://github.com/raysan5/raylib/releases or `winget install raysan5.raylib`

**Linux (Ubuntu/Debian)**
```sh
sudo apt install libraylib-dev
```
For raylib 5.5, build from source: https://github.com/raysan5/raylib
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

## Architecture

Immediate Mode drawing pattern. Drawing functions are called every frame to construct the UI; state is centrally managed in `data.zig`. The raylib C API is called via `@cImport` bindings.

```
src/
├── main.zig        # entry point · raylib initialization · main loop
├── data.zig        # AppState · Todo · TabFilter state management
├── raylib.zig      # raylib @cImport bindings
├── theme.zig       # color and font constants
└── components/     # drawing components for input, tabs, and Todo list
```