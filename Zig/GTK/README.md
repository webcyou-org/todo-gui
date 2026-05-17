# Zig / GTK4 Todo

GTK4 GUI Todo app written in Zig 0.16.0 using manual `extern fn` bindings (no `@cImport` — Zig's `translate-c` crashes on GTK4's complex headers in 0.16.0).

## Requirements

- [Zig](https://ziglang.org/) 0.16.0
- GTK4

## Install

**macOS**
```sh
brew install zig gtk4
```

**Windows**
```sh
winget install zig.zig
```
Install GTK4 via MSYS2: `pacman -S mingw-w64-x86_64-gtk4`

**Linux (Ubuntu/Debian)**
```sh
sudo apt install libgtk-4-dev
```
Install Zig from https://ziglang.org/download/ or `snap install zig --classic --channel 0.16/stable`

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