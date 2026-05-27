# Gio Todo

Go Todo app using [Gio](https://gioui.org/) v0.7 — immediate mode GUI toolkit.

## Requirements

- Go 1.23+

**macOS**
```sh
xcode-select --install
brew install go
```

**Windows**
```sh
winget install GoLang.Go
```

**Linux (Ubuntu/Debian)**
```sh
sudo apt install golang-go
```

## Install

```sh
go mod download
```

## Run

Works on all platforms:
```sh
go run .
```

## Architecture

Gio の即時モード UI パターン。フレームイベントごとに `layout` 関数を呼び出して UI を宣言的に描画し、状態は `data/` パッケージで管理する。

```
.
├── main.go         # エントリーポイント・app.Window・イベントループ
├── data/           # Todo データモデル・TabFilter・状態管理
├── ui/             # 入力欄・タブ・リストの Gio レイアウト関数
└── theme/          # カラー・フォント定数
```