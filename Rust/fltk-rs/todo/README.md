# ToDo - fltk-rs

Todo application implemented with Rust + [fltk-rs](https://github.com/fltk-rs/fltk-rs) (FLTK).

## Requirements

- Rust (stable)
- C++ compiler (g++ or clang++)
- cmake

Install Rust via https://rustup.rs/ or `winget install Rustlang.Rustup` on Windows.

### macOS

```bash
# Xcode Command Line Tools provide cmake and clang++
xcode-select --install
```

### Windows

```sh
winget install Kitware.CMake
```
Install Visual Studio Build Tools (C++ workload) from https://visualstudio.microsoft.com/visual-cpp-build-tools/

### Ubuntu / Debian

```bash
sudo apt-get install cmake g++ libx11-dev libxext-dev libxft-dev libxinerama-dev libxcursor-dev libxrender-dev libxfixes-dev libpango1.0-dev libgl1-mesa-dev libglu1-mesa-dev
```

## Build & Run

```bash
cargo run
```

## Architecture

Single-package structure using fltk-rs FLTK Rust bindings. Data model and theme are separated into files; `main.rs` constructs the window and widgets.

```
src/
├── main.rs         # entry point · app::App · window construction · event loop
├── data.rs         # Todo data model · TabFilter · AppState
└── theme.rs        # color and style constants
```