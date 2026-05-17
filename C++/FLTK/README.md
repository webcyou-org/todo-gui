# FLTK Todo

C++ Todo app using [FLTK](https://www.fltk.org/) (Fast Light Toolkit).

## Requirements

- CMake 3.15+
- FLTK

## Install

**macOS**
```sh
brew install cmake fltk
```

**Windows**
```sh
winget install Kitware.CMake
```
Download FLTK from https://www.fltk.org/software.php or `winget install FLTK.FLTK`

**Linux (Ubuntu/Debian)**
```sh
sudo apt install cmake build-essential libfltk1.3-dev
```

## Build

```sh
cmake -B build
cmake --build build
```

## Run

```sh
open build/main.app
```

> macOS でビルドすると `.app` バンドルが生成されます。

## Architecture

単一ファイルに近いシンプルな構成。FLTK ウィジェットを直接組み立て、データとロジックを C++ クラスで一体管理する。

```
src/
├── main.cpp        # エントリーポイント・ウィンドウ構築・イベントループ
├── data.h          # Todo データモデル・AppState・TabFilter
├── theme.h         # カラー定数・デザイントークン
└── widgets/        # 入力欄・タブ・リストの FLTK ウィジェット部品
```