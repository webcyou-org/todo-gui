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

Electron のメインプロセスと Chromium レンダラーの 2 プロセス構成。Vanilla HTML/CSS/JS でフロントエンドを実装し、IPC なしにシンプルに完結する。

```
.
├── main.js         # メインプロセス・BrowserWindow 起動・ウィンドウ設定
├── renderer.js     # レンダラープロセス・Todo ロジック・DOM 操作
├── index.html      # アプリ画面 HTML
└── src/            # CSS・追加 JS アセット
```