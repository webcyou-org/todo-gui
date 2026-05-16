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
cargo run
```

## Architecture

rui の宣言的 GPU レンダリング UI パターン。状態は `State` マクロで管理し、ビュー関数がフレームごとに UI ツリーを返す関数型スタイル。

```
src/
├── main.rs         # エントリーポイント・rui::rui・ルートビュー定義・状態管理
├── data.rs         # Todo データモデル・TabFilter・AppState
└── theme.rs        # カラー定数
```
