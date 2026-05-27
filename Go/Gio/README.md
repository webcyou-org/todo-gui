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

Gio's immediate mode UI pattern. The `layout` function is called on every frame event to declaratively render the UI; state is managed in the `data/` package.

```
.
├── main.go         # entry point · app.Window · event loop
├── data/           # Todo data model · TabFilter · state management
├── ui/             # Gio layout functions for input, tabs, and list
└── theme/          # color and font constants
```