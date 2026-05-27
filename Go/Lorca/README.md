# Lorca Todo

Go Todo app using [Lorca](https://github.com/zserge/lorca) — builds desktop apps with Go and HTML/CSS, using Chrome as the UI layer.

## Requirements

- Go 1.20+
- Google Chrome or Chromium installed

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

A two-layer structure with a Go backend and an HTML/CSS/JS frontend. Lorca launches a Chrome window and provides a bridge so that Go functions can be called from JavaScript.

```
.
├── main.go             # entry point · Lorca window launch · Go function binding
└── frontend/           # frontend UI in HTML, CSS, and JS
```