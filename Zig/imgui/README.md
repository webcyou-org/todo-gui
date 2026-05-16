# Zig / Dear ImGui Todo

Todo application built with [Zig](https://ziglang.org/) 0.16.0 and [Dear ImGui](https://github.com/ocornut/imgui) using GLFW + OpenGL3 backend.

## Requirements

- macOS (arm64 / x86_64)
- [Zig](https://ziglang.org/) 0.16.0
- [GLFW](https://www.glfw.org/) 3.4

```sh
brew install zig glfw
```

## Build

```sh
zig build
```

## Run

```sh
zig build run
```

Or run the built binary directly:

```sh
./zig-out/bin/todo
```

## Notes

Dear ImGui source is vendored from the [C++/ImGui](../../../C++/ImGui/vendor/imgui) implementation via symlink.  
The C++ wrapper (`src/imgui_app.cpp`) exposes a minimal C API that the Zig code calls via `@cImport`.

## Architecture

即時モード GUI パターン。Zig がデータモデルと状態を管理し、C++ ラッパーが Dear ImGui を GLFW + OpenGL3 で描画する。`@cImport` で C API を呼び出す。

```
src/
├── main.zig        # エントリーポイント・ウィンドウ初期化・メインループ
├── data.zig        # AppState・Todo・TabFilter の状態管理
├── imgui_app.h/cpp # Dear ImGui + GLFW + OpenGL3 の C++ ラッパー（最小 C API）
└── components/     # 入力欄・タブ・Todo リストの ImGui ウィジェット関数（Zig）
vendor/imgui/       # Dear ImGui ソース（C++/ImGui からシムリンク）
```