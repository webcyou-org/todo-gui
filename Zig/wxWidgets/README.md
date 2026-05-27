# Zig / wxWidgets Todo

Dark-theme Todo app implemented with Zig + wxWidgets 3.3.  
Data model and CRUD logic are implemented in Zig; the wxWidgets UI is called via a C++ wrapper.

## Architecture

```
Zig side  : data.zig  — Todo / AppState / CRUD (export fn → called from C++)
C++ side  : wx_app.cpp + widgets/ — wxWidgets UI (calls Zig-exported C functions)
Bridge    : wx_bridge.h — shared C-compatible structs (WxTodo, WxAppState, WxTabFilter)
```

## Requirements

- macOS (Cocoa backend)
- [Zig](https://ziglang.org/) 0.16.0+
- wxWidgets 3.3+ (`brew install wxwidgets`)

## Install

```sh
brew install wxwidgets
```

## Build

```sh
zig build
```

The first build takes a few seconds due to link processing.

## Run

```sh
zig build run
# or
./zig-out/bin/todo
```