# Zig / GTK4 Todo

GTK4 GUI Todo app written in Zig 0.16.0 using manual `extern fn` bindings (no `@cImport` — Zig's `translate-c` crashes on GTK4's complex headers in 0.16.0).

## Requirements

- macOS (Apple Silicon recommended)
- [Zig](https://ziglang.org/) 0.16.0
- GTK4 (`brew install gtk4`)

## Install

```sh
brew install gtk4
```

## Build

```sh
zig build
```

## Run

```sh
zig build run
# or directly
./zig-out/bin/todo
```

## Architecture

GTK4 を手書き `extern fn` バインディングで呼び出すシングルパッケージ構成（`@cImport` は GTK4 のヘッダー複雑性で使用不可）。データとコンポーネントをファイルで分離する。

```
src/
├── main.zig        # エントリーポイント・GtkApplication・ウィンドウ構築
├── data.zig        # AppState・Todo・TabFilter の状態管理
├── bindings.zig    # GTK4 手書き extern fn バインディング
├── ctx.zig         # コールバック用コンテキスト型
└── components/     # 入力欄・タブ・Todo リストの GTK4 ウィジェット部品
```