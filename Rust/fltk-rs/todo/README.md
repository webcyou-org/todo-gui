# ToDo - fltk-rs

Rust + [fltk-rs](https://github.com/fltk-rs/fltk-rs) (FLTK) で実装した ToDo アプリケーション。

## Requirements

- Rust (stable)
- C++ compiler (g++ or clang++)
- cmake

### Ubuntu / Debian

```bash
sudo apt-get install cmake g++ libx11-dev libxext-dev libxft-dev libxinerama-dev libxcursor-dev libxrender-dev libxfixes-dev libpango1.0-dev libgl1-mesa-dev libglu1-mesa-dev
```

### macOS

```bash
# Xcode Command Line Tools provide cmake and clang++
xcode-select --install
```

## Build & Run

```bash
cd Rust/fltk-rs/todo
cargo run
```
