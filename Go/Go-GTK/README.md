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

A single-package structure that calls GTK2 bindings directly. Data model and widget functions are separated into files; `main.go` constructs the window.

```
.
├── main.go         # entry point · gtk.Init · window construction
├── data.go         # Todo data model · TabFilter · state management
├── input.go        # input field widget
├── tabs.go         # tab menu widget
├── todo_list.go    # Todo list widget
└── theme.go        # color and style constants
```