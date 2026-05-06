# ToDo - rui

Rust + [rui](https://github.com/audulus/rui) (GPU-rendered declarative UI) で実装した ToDo アプリケーション。

## Requirements

- Rust (stable)
- GPU support (Vulkan/Metal/DX12)

### Ubuntu / Debian

```bash
sudo apt-get install cmake g++ libx11-dev libxext-dev libxft-dev libxinerama-dev libxcursor-dev libxrender-dev libxfixes-dev libgl1-mesa-dev libglu1-mesa-dev
```

### macOS

```bash
xcode-select --install
```

## Build & Run

```bash
cd Rust/rui/todo
cargo run
```
