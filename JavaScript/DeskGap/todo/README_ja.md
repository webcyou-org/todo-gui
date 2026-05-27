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

Node.js メインプロセスとシステム WebView レンダラーの 2 プロセス構成。DeskGap が IPC を提供し、ネイティブ機能をレンダラーから呼び出せる。

```
.
├── index.js        # メインプロセス・DeskGap アプリ起動・ウィンドウ設定
└── index.html      # レンダラー（HTML/CSS/JS による UI）
```