# Zig / GTK4 Todo

GTK4 GUI Todo app written in Zig 0.16.0 using manual `extern fn` bindings (no `@cImport` — Zig's `translate-c` crashes on GTK4's complex headers in 0.16.0).

## Requirements

- macOS (Apple Silicon recommended)
- [Zig](https://ziglang.org/) 0.16.0
- GTK4 (`brew install gtk4`)

## Install

```sh
brew install gtk4
```

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