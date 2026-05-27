# Lorca Todo

Go Todo app using [Lorca](https://github.com/zserge/lorca) — builds desktop apps with Go and HTML/CSS, using Chrome as the UI layer.

## Requirements

- Go 1.20+
- Google Chrome または Chromium インストール済み

**macOS**
```sh
brew install go
brew install --cask google-chrome
```

**Windows**
```sh
winget install GoLang.Go
winget install Google.Chrome
```

**Linux (Ubuntu/Debian)**
```sh
sudo apt install golang-go
```
Install Chrome from https://www.google.com/chrome/ or install Chromium: `sudo apt install chromium-browser`

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

Go バックエンドと HTML/CSS/JS フロントエンドの 2 層構成。Lorca が Chrome ウィンドウを起動し、Go 側の関数を JavaScript から呼び出せるよう bridge を提供する。

```
.
├── main.go             # エントリーポイント・Lorca ウィンドウ起動・Go 関数のバインド
└── frontend/           # HTML・CSS・JS によるフロントエンド UI
```