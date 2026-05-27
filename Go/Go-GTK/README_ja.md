# Go-GTK Todo

Go Todo app using [go-gtk](https://github.com/mattn/go-gtk) (GTK2 bindings for Go).

## Requirements

- Go 1.23+
- GTK2

**macOS**
```sh
brew install go gtk+
```

**Windows**
```sh
winget install GoLang.Go
```
Install GTK2 via MSYS2: `pacman -S mingw-w64-x86_64-gtk2`

**Linux (Ubuntu/Debian)**
```sh
sudo apt install golang-go libgtk2.0-dev
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

GTK2 バインディングを直接呼び出すシングルパッケージ構成。データモデルとウィジェット関数をファイルで分離し、`main.go` がウィンドウを構築する。

```
.
├── main.go         # エントリーポイント・gtk.Init・ウィンドウ構築
├── data.go         # Todo データモデル・TabFilter・状態管理
├── input.go        # 入力フィールドウィジェット
├── tabs.go         # タブメニューウィジェット
├── todo_list.go    # Todo リストウィジェット
└── theme.go        # カラー・スタイル定数
```