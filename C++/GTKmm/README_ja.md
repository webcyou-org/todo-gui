# GTKmm Todo

C++ Todo app using [gtkmm](https://gtkmm.org/) 3 (C++ wrappers for GTK).

## Requirements

- CMake 3.15+
- gtkmm-3.0
- pkg-config

## Install

**macOS**
```sh
brew install cmake gtkmm3 pkg-config
```

**Windows**
```sh
winget install Kitware.CMake
```
Install gtkmm via MSYS2: `pacman -S mingw-w64-x86_64-gtkmm4`

**Linux (Ubuntu/Debian)**
```sh
sudo apt install cmake build-essential libgtkmm-3.0-dev pkg-config
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

gtkmm の C++ ウィジェットクラスを継承・組み合わせるオブジェクト指向構成。データモデルとウィジェット部品をファイルで分離する。

```
src/
├── main.cpp        # エントリーポイント・Gtk::Application・ウィンドウ構築
├── data.h          # Todo データモデル・AppState・TabFilter
├── theme.h         # カラー定数・デザイントークン
├── cairo_util.h    # Cairo 描画ユーティリティ
└── widgets/        # 入力欄 (todo_input)・タブ (tab_menu)・リスト (todo_list)
```