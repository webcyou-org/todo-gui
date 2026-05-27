# ToDo - rui

Todo application implemented with Rust + [rui](https://github.com/audulus/rui) (GPU-rendered declarative UI).

## Requirements

- Rust (stable)
- GPU support (Vulkan/Metal/DX12)

Install Rust via https://rustup.rs/ or `winget install Rustlang.Rustup` on Windows.

### macOS

```bash
xcode-select --install
```

### Windows

```sh
winget install Kitware.CMake
```
Install Visual Studio Build Tools (C++ workload) from https://visualstudio.microsoft.com/visual-cpp-build-tools/

### Ubuntu / Debian

```bash
sudo apt-get install cmake g++ libx11-dev libxext-dev libxft-dev libxinerama-dev libxcursor-dev libxrender-dev libxfixes-dev libgl1-mesa-dev libglu1-mesa-dev
```

## Build & Run

```bash
cargo run
```

## Architecture

rui's declarative GPU-rendered UI pattern. State is managed with the `State` macro; view functions return a UI tree each frame in a functional style.

```
src/
├── main.rs         # entry point · rui::rui · root view definition · state management
├── data.rs         # Todo data model · TabFilter · AppState
└── theme.rs        # color constants
```