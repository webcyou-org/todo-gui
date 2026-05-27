# Dear ImGui Todo

C++ Todo app using [Dear ImGui](https://github.com/ocornut/imgui) with OpenGL3 + GLFW backend.  
ImGui sources are bundled under `vendor/imgui/`.

## Requirements

- CMake 3.15+
- GLFW3
- OpenGL

## Install

**macOS**
```sh
brew install cmake glfw
```

**Windows**
```sh
winget install Kitware.CMake
```
Download GLFW from https://www.glfw.org/download or `winget install GLFW.GLFW`

**Linux (Ubuntu/Debian)**
```sh
sudo apt install cmake build-essential libglfw3-dev
```

## Build

```sh
cmake -B build
cmake --build build
```

## Run

```sh
./build/main
```

## Architecture

即時モード GUI（Immediate Mode）パターン。毎フレーム描画関数を呼び出し、状態は `AppState` 構造体で一元管理する。ImGui ソースは `vendor/imgui/` にバンドルされている。

```
src/
├── main.cpp        # エントリーポイント・GLFW ウィンドウ・メインループ
├── data.h          # AppState・Todo・TabFilter の状態管理
├── theme.h         # カラー・スタイル定数
└── widgets/        # 入力欄・タブ・リストの ImGui ウィジェット関数
vendor/imgui/       # Dear ImGui ソース（バンドル）
```