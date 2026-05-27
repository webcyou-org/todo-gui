# Fyne Todo

Go Todo app using [Fyne](https://fyne.io/) v2 — cross-platform GUI toolkit.

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

データとテーマを専用パッケージに分離し、`main.go` がアプリウィンドウを構築する構成。Fyne のウィジェット API で UI を組み立てる。

```
.
├── main.go         # エントリーポイント・fyne.App・ウィンドウ構築
├── data/           # Todo データモデル・TabFilter・状態管理
├── ui/             # 入力欄・タブ・リストの Fyne ウィジェット
└── apptheme/       # カスタムテーマ・カラー定数
```