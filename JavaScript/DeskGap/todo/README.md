# DeskGap Todo

Node.js Todo app using [DeskGap](https://deskgap.com/) — lightweight Electron alternative using the system WebView.

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

A two-process structure with a Node.js main process and a system WebView renderer. DeskGap provides IPC so that native features can be called from the renderer.

```
.
├── index.js        # main process · DeskGap app launch · window configuration
└── index.html      # renderer (UI via HTML/CSS/JS)
```