# Zig / raylib Todo

Todo application built with [Zig](https://ziglang.org/) 0.16.0 and [raylib](https://www.raylib.com/) 5.5.

## Requirements

- [Zig](https://ziglang.org/) 0.16.0
- [raylib](https://www.raylib.com/) 5.5

## Install

**macOS**
```sh
brew install zig raylib
```

**Windows**
```sh
winget install zig.zig
```
Download raylib from https://github.com/raysan5/raylib/releases or `winget install raysan5.raylib`

**Linux (Ubuntu/Debian)**
```sh
sudo apt install libraylib-dev
```
For raylib 5.5, build from source: https://github.com/raysan5/raylib
Install Zig from https://ziglang.org/download/ or `snap install zig --classic --channel 0.16/stable`

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

## Architecture

即時モード描画パターン。毎フレーム描画関数を呼び出して UI を構築し、状態は `data.zig` で一元管理する。raylib の `@cImport` バインディングで C API を呼び出す。

```
src/
├── main.zig        # エントリーポイント・raylib 初期化・メインループ
├── data.zig        # AppState・Todo・TabFilter の状態管理
├── raylib.zig      # raylib @cImport バインディング
├── theme.zig       # カラー・フォント定数
└── components/     # 入力欄・タブ・Todo リストの描画コンポーネント
```