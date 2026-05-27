# bgfx + Dear ImGui Todo

C++ Todo app using [bgfx](https://github.com/bkaradzic/bgfx) (cross-platform rendering) with Dear ImGui, rendered via Metal on macOS.

## Requirements

- CMake 3.20+
- GLFW3
- macOS: Xcode Command Line Tools (Metal backend)

## Install

**macOS**
```sh
xcode-select --install
brew install cmake glfw
```

**Windows**
```sh
winget install Kitware.CMake
```
Download GLFW from https://www.glfw.org/download or `winget install GLFW.GLFW`

> Note: bgfx supports DirectX on Windows instead of Metal. You may need to adjust the backend in `src/main.cpp`.

**Linux (Ubuntu/Debian)**
```sh
sudo apt install cmake build-essential libglfw3-dev
```

bgfx is fetched automatically via CMake FetchContent on first build (requires network access, takes several minutes).

## Build

```sh
cmake -B build
cmake --build build
```

## Run

```sh
./build/todo
```

## Architecture

即時モード GUI パターン。bgfx が Metal（macOS）でレンダリングを担い、Dear ImGui が UI を描画する。GLFW でウィンドウ・入力を管理し、状態は `AppState` 構造体で一元管理する。

```
src/
├── main.cpp                # エントリーポイント・bgfx/GLFW 初期化・メインループ
├── data.h                  # AppState・Todo・TabFilter
├── theme.h                 # カラー・スタイル定数
├── imgui_bgfx_backend.h/cpp# bgfx 用 ImGui レンダリングバックエンド
├── metal_window.h/mm       # macOS Metal ネイティブウィンドウ取得
└── widgets/                # 入力欄・タブ・リストの ImGui ウィジェット関数
```