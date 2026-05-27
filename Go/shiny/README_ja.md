# shiny Todo

Go Todo app using [golang.org/x/exp/shiny](https://pkg.go.dev/golang.org/x/exp/shiny) — experimental Go GUI package.

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

shiny の低レベルウィンドウ API を使った即時描画構成。フレームイベントで画面全体を再描画し、状態は `data.go` で管理する。

```
.
├── main.go         # エントリーポイント・shiny ウィンドウ・イベントループ
├── data.go         # Todo データモデル・TabFilter・AppState
├── render.go       # 画面全体のレンダリング関数
├── draw.go         # 基本図形描画ユーティリティ
├── widget_input.go # 入力フィールドウィジェット
├── widget_tabs.go  # タブメニューウィジェット
└── widget_todo.go  # Todo リストウィジェット
```