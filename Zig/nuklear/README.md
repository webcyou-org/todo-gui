# Todo — Zig + Nuklear

A dark-theme Todo application built with [Zig](https://ziglang.org/) 0.16.0 and [Nuklear](https://github.com/Immediate-Mode-UI/Nuklear) (immediate-mode GUI) using the SDL2 Renderer backend.

## Requirements

- **Zig** 0.16.0
- **SDL2**

**macOS**
```sh
brew install zig sdl2
```

**Windows**
```sh
winget install zig.zig
```
Download SDL2 from https://github.com/libsdl-org/SDL/releases or `winget install SDL.SDL2`

**Linux (Ubuntu/Debian)**
```sh
sudo apt install libsdl2-dev
```
Install Zig from https://ziglang.org/download/ or `snap install zig --classic --channel 0.16/stable`

## Build

```sh
zig build
```

## Run

```sh
zig build run
# or
./zig-out/bin/todo
```

## Project Structure

```
src/
├── main.zig                  # Entry point + main loop
├── data.zig                  # AppState, Todo, TabFilter
├── nk.zig                    # Shared @cImport for nk_app.h
├── nk_app.h                  # C wrapper declarations (safe for @cImport)
├── nk_app.c                  # C wrapper implementation (SDL2 + Nuklear)
├── nuklear_impl.c            # NK_IMPLEMENTATION + NK_SDL_RENDERER_IMPLEMENTATION
└── components/
    ├── input.zig             # Input field component
    ├── tabs.zig              # Tab menu (All / Active / Completed)
    └── todo_list.zig         # Todo list with custom-drawn items
vendor/
├── nuklear.h                 # Nuklear 4.9.4 (single-header)
├── nuklear_sdl_renderer.h    # SDL2 Renderer backend
└── nuklear_config.h          # Feature flags
```

## Notes

Zig 0.16.0's `@cImport` translate-C pipeline cannot process SDL2's ARM NEON headers on Apple Silicon. The `nk_app.h/c` wrapper isolates all SDL2 and Nuklear headers inside regular C compilation units (which work fine), exposing a minimal opaque API to Zig.

## Architecture

Immediate Mode GUI pattern. Zig manages the data model and state; the C wrapper (`nk_app.h/c`) handles SDL2 + Nuklear rendering. To avoid SDL2's translate-C issue, Nuklear/SDL2 headers are isolated in C compilation units.

```
src/
├── main.zig                # entry point · main loop
├── data.zig                # AppState · Todo · TabFilter state management
├── nk.zig                  # @cImport for nk_app.h
├── nk_app.h/c              # C wrapper for SDL2 + Nuklear (minimal API for Zig)
├── nuklear_impl.c          # NK_IMPLEMENTATION · NK_SDL_RENDERER_IMPLEMENTATION
└── components/             # Nuklear widget functions for input, tabs, and Todo list
vendor/                     # Nuklear headers (single-header library)
```