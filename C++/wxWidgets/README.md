# wxWidgets Todo

C++ Todo app using [wxWidgets](https://www.wxwidgets.org/).  
wxWidgets itself is built from source via CMake ExternalProject (`thirdparty/wxwidgets/`).

## Requirements

- CMake 3.6+
- pkg-config
- macOS: Xcode Command Line Tools

## Install

**macOS**
```sh
xcode-select --install
brew install cmake pkg-config
```

**Windows**
```sh
winget install Kitware.CMake
```
wxWidgets is built from source (bundled via CMake ExternalProject — no separate install needed).

**Linux (Ubuntu/Debian)**
```sh
sudo apt install cmake build-essential pkg-config libgtk-3-dev
```
wxWidgets is built from source (bundled via CMake ExternalProject — no separate install needed).

## Build

初回ビルドは wxWidgets のコンパイルを含むため数分かかります。

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

## Run

```sh
./build/subprojects/Build/todo_core/todo
```

## Architecture

純 C++ 実装。wxWidgets ウィジェットを継承・組み合わせてイベント駆動 UI を構築し、データモデルとウィジェット部品をファイルで分離する。wxWidgets 本体は CMake ExternalProject でソースビルドする。

```
src/
├── main.cpp        # エントリーポイント・wxApp・メインウィンドウ構築
├── data.h          # Todo データモデル・AppState・TabFilter
├── theme.h         # カラー・スタイル定数
└── widgets/        # 入力欄・タブ・リストの wxWidgets ウィジェット部品
thirdparty/wxwidgets/   # wxWidgets ソース（CMake ExternalProject）
```