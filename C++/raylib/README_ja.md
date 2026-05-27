# raylib Todo

C++ Todo app using [raylib](https://www.raylib.com/).

## Requirements

- clang++
- raylib 5.5
- pkg-config

## Install

**macOS**
```sh
brew install raylib pkg-config
```

**Windows**
Download raylib from https://github.com/raysan5/raylib/releases or `winget install raysan5.raylib`

**Linux (Ubuntu/Debian)**
```sh
sudo apt install libraylib-dev pkg-config
```
For raylib 5.5, build from source: https://github.com/raysan5/raylib

## Build

```sh
make
```

## Run

```sh
./todo
```

## Architecture

即時モード描画パターン。raylib のフレームループ内で毎フレーム UI を描画し、状態は `AppState` 構造体で一元管理する。

```
src/
├── main.cpp        # エントリーポイント・ウィンドウ初期化・メインループ
├── data.h          # AppState・Todo・TabFilter
├── theme.h         # カラー・フォント定数
├── draw_helpers.h  # 丸角矩形などの描画ユーティリティ
└── components/     # 入力欄・タブ・リストの描画コンポーネント
```