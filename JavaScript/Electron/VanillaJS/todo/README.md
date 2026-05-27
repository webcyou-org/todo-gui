# Electron (Vanilla JS) Todo

JavaScript Todo app using [Electron](https://www.electronjs.org/) with vanilla HTML/CSS/JS.

## Requirements

- Node.js 18+

**macOS**: `brew install node`
**Windows**: `winget install OpenJS.NodeJS`
**Linux (Ubuntu/Debian)**: `sudo apt install nodejs npm`

## Install

```sh
npm install
```

## Run

```sh
npm start
```

## Architecture

A two-process structure with an Electron main process and a Chromium renderer. The frontend is implemented in vanilla HTML/CSS/JS, keeping it simple and self-contained without IPC.

```
.
├── main.js         # main process · BrowserWindow launch · window configuration
├── renderer.js     # renderer process · Todo logic · DOM manipulation
├── index.html      # app screen HTML
└── src/            # CSS and additional JS assets
```