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

Data and theme are separated into dedicated packages; `main.go` constructs the app window. The UI is assembled using Fyne's widget API.

```
.
├── main.go         # entry point · fyne.App · window construction
├── data/           # Todo data model · TabFilter · state management
├── ui/             # Fyne widget components for input, tabs, and list
└── apptheme/       # custom theme · color constants
```