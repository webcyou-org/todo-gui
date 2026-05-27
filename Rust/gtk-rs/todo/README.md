# ToDo - gtk-rs

Todo application implemented with Rust + [gtk-rs](https://gtk-rs.org/) (GTK4).

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

Single-package structure using gtk-rs GTK4 Rust bindings. Data model and theme are separated into files; `main.rs` constructs the GTK4 application.

```
src/
├── main.rs         # entry point · gtk::Application · window construction
├── data.rs         # Todo data model · TabFilter · AppState
└── theme.rs        # color and CSS constants
```