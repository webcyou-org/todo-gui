# Zig / raylib Todo

Todo application built with [Zig](https://ziglang.org/) 0.16.0 and [raylib](https://www.raylib.com/) 5.5.

## Requirements

- macOS (arm64 / x86_64)
- [Zig](https://ziglang.org/) 0.16.0
- [raylib](https://www.raylib.com/) 5.5 (installed at `/opt/homebrew/Cellar/raylib/5.5`)

## Install

```sh
brew install zig
brew install raylib
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