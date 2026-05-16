# Lorca Todo

Go Todo app using [Lorca](https://github.com/zserge/lorca) — builds desktop apps with Go and HTML/CSS, using Chrome as the UI layer.

## Requirements

- Go 1.20+
- Google Chrome または Chromium インストール済み

```sh
brew install go
brew install --cask google-chrome
```

## Install

```sh
go mod download
```

## Run

```sh
go run .
```

## Architecture

Go バックエンドと HTML/CSS/JS フロントエンドの 2 層構成。Lorca が Chrome ウィンドウを起動し、Go 側の関数を JavaScript から呼び出せるよう bridge を提供する。

```
.
├── main.go             # エントリーポイント・Lorca ウィンドウ起動・Go 関数のバインド
└── frontend/           # HTML・CSS・JS によるフロントエンド UI
```