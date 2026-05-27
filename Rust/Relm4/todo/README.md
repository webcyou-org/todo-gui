# ToDo - Relm4

Todo application implemented with Rust + [Relm4](https://relm4.org/) (GTK4).

## Requirements

- Rust (stable)
- GTK4 development libraries

Install Rust via https://rustup.rs/ or `winget install Rustlang.Rustup` on Windows.

### macOS

```bash
brew install gtk4
```

### Windows

Install GTK4 via MSYS2: `pacman -S mingw-w64-x86_64-gtk4`

### Ubuntu / Debian

```bash
sudo apt-get install libgtk-4-dev
```

## Build & Run

```bash
cargo run
```

## Architecture

Relm4's Elm-inspired MVC pattern (Model / Update / View). GTK4 widgets are declared with Relm4 macros; components are separated into files.

```
src/
├── main.rs         # entry point · RelmApp launch · root component definition
├── data.rs         # AppState · Todo · TabFilter · Message type definitions
├── theme.rs        # color and CSS constants
└── components/     # Relm4 components for input, tabs, and Todo list
```