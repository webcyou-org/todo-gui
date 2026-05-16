# Todo — Zig + Nuklear

A dark-theme Todo application built with [Zig](https://ziglang.org/) 0.16.0 and [Nuklear](https://github.com/Immediate-Mode-UI/Nuklear) (immediate-mode GUI) using the SDL2 Renderer backend.

## Requirements

- **Zig** 0.16.0
- **SDL2** (via Homebrew)

```sh
brew install sdl2
```

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