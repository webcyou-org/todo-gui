# Neutralinojs Todo

JavaScript Todo app using [Neutralinojs](https://neutralino.js.org/) — lightweight desktop app framework using the system WebView (no bundled browser engine).

## Requirements

- Node.js 18+
- Neutralinojs CLI

**macOS**: `brew install node`
**Windows**: `winget install OpenJS.NodeJS`
**Linux (Ubuntu/Debian)**: `sudo apt install nodejs npm`

```sh
npm install -g @neutralinojs/neu
```

## Install

```sh
neu update
```

## Run

```sh
neu run
```

## Build (distribution binary)

```sh
neu build
# Output: dist/
```

## Architecture

A lightweight two-layer structure. Neutralinojs provides a thin native runtime (no bundled browser) and displays the frontend via the system WebView.

```
.
├── neutralino.config.json  # app configuration (entry point · window settings)
└── resources/              # frontend UI in HTML, CSS, and JS
```