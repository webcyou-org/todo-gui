# Zig / wxWidgets Todo

Zig + wxWidgets 3.3 で実装したダークテーマ Todo アプリ。  
データモデル・CRUD ロジックを Zig で実装し、wxWidgets UI を C++ ラッパー経由で呼び出す構成。

## Architecture

```
Zig side  : data.zig  — Todo / AppState / CRUD (export fn → called from C++)
C++ side  : wx_app.cpp + widgets/ — wxWidgets UI (calls Zig-exported C functions)
Bridge    : wx_bridge.h — shared C-compatible structs (WxTodo, WxAppState, WxTabFilter)
```

## Requirements

- macOS (Cocoa backend)
- [Zig](https://ziglang.org/) 0.16.0+
- wxWidgets 3.3+ (`brew install wxwidgets`)

## Install

```sh
brew install wxwidgets
```

## Build

```sh
zig build
```

初回ビルドはリンク処理に数秒かかります。

## Run

```sh
zig build run
# または
./zig-out/bin/todo
```