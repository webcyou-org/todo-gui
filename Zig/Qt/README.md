# Zig / Qt Todo

Todo app implemented with Zig + Qt6 Widgets.  
Zig manages the data model, Qt6 C++ handles the UI, and the two communicate bidirectionally via a C bridge.

## Requirements

- macOS (arm64)
- [Zig](https://ziglang.org/) 0.16.0
- Qt 6 (`brew install qt`)

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

## File Structure

```
src/
├── main.zig       # entry point + C callbacks + pushUI()
├── data.zig       # AppState / Todo / TabFilter data model
├── qt_bridge.h    # C interface declarations for Zig↔Qt
├── qt_app.cpp     # full UI implementation via Qt6 Widgets
└── theme.h        # design token constants (colors · sizes)
```

## Architecture

MVC pattern. Zig holds the data model, Qt6 C++ handles the View.  
Callbacks are called bidirectionally via the C function bridge (`qt_bridge.h`).

| Layer | File | Role |
|-------|------|------|
| Model | `data.zig` | AppState · Todo list · TabFilter state management |
| View | `qt_app.cpp` | UI rendering and event handling via Qt Widgets |
| Controller | `main.zig` | `export fn` callbacks bridge Qt→Zig; `pushUI()` pushes Zig→Qt updates |

## Notes

- `callconv(.c)` **lowercase** — C calling convention in Zig 0.14+ (`.C` uppercase is deprecated)
- Bidirectional C bridge built with `export fn` + `extern fn` — no Q_OBJECT / MOC needed
- All signals connected via lambda `connect(widget, &Signal, lambda)` — no custom Q_OBJECT class required
- `QStyleFactory::create("Fusion")` — switches from the macOS native style to Fusion so that QStyleSheet is fully applied
- `deleteLater()` — Qt idiom for safely deleting a widget from within a signal handler
- Placeholder text color set via `QPalette::PlaceholderText` (the `color` property in stylesheet may not work)
- `on_ready` callback — called after Qt-side UI setup completes; pumps initial data via `qt_update_todos`