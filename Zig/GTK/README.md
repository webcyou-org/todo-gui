# Zig / GTK4 Todo

GTK4 GUI Todo app written in Zig 0.16.0 using manual `extern fn` bindings (no `@cImport` — Zig's `translate-c` crashes on GTK4's complex headers in 0.16.0).

## Requirements

- [Zig](https://ziglang.org/) 0.16.0
- GTK4

## Install

**macOS**
```sh
brew install zig gtk4
```

**Windows**
```sh
winget install zig.zig
```
Install GTK4 via MSYS2: `pacman -S mingw-w64-x86_64-gtk4`

**Linux (Ubuntu/Debian)**
```sh
sudo apt install libgtk-4-dev
```
Install Zig from https://ziglang.org/download/ or `snap install zig --classic --channel 0.16/stable`

## Build

```sh
zig build
```

## Run

```sh
zig build run
# or directly
./zig-out/bin/todo
```

## Architecture

A single-package structure that calls GTK4 via hand-written `extern fn` bindings (`@cImport` cannot be used due to GTK4's header complexity). Data and components are separated into files.

```
src/
├── main.zig        # entry point · GtkApplication · window construction
├── data.zig        # AppState · Todo · TabFilter state management
├── bindings.zig    # GTK4 hand-written extern fn bindings
├── ctx.zig         # context types for callbacks
└── components/     # GTK4 widget components for input, tabs, and Todo list
```