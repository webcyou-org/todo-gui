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

An immediate-drawing structure using shiny's low-level window API. The entire screen is redrawn on each frame event; state is managed in `data.go`.

```
.
├── main.go         # entry point · shiny window · event loop
├── data.go         # Todo data model · TabFilter · AppState
├── render.go       # full-screen rendering function
├── draw.go         # basic shape drawing utilities
├── widget_input.go # input field widget
├── widget_tabs.go  # tab menu widget
└── widget_todo.go  # Todo list widget
```