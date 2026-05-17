# GTK4 Todo

C++ Todo app using [GTK4](https://gtk.org/).

## Requirements

- clang++
- GTK4
- pkg-config

## Install

**macOS**
```sh
brew install gtk4 pkg-config
```

**Windows**
Install GTK4 via MSYS2: `pacman -S mingw-w64-x86_64-gtk4`

**Linux (Ubuntu/Debian)**
```sh
sudo apt install libgtk-4-dev pkg-config
```

## Build

```sh
make
```

## Run

```sh
./todo
```

## Architecture

GTK4 C API を直接利用するシングルバイナリ構成。データモデルとウィジェット構築をファイルで分離し、Cairo でカスタム描画を行う。

```
src/
├── main.cpp        # エントリーポイント・GtkApplication・ウィンドウ構築
├── data.h          # Todo データモデル・AppState・TabFilter
├── app.h           # アプリケーション状態・ウィジェット参照
├── theme.h         # カラー定数・デザイントークン
├── cairo_util.h    # Cairo 描画ユーティリティ
└── widgets/        # 入力欄・タブ・リストの GTK4 ウィジェット部品
```