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

## Build（配布バイナリ）

```sh
neu build
# 出力先: dist/
```

## Architecture

軽量な 2 層構成。Neutralinojs が薄いネイティブランタイム（バンドルブラウザなし）を提供し、システム WebView でフロントエンドを表示する。

```
.
├── neutralino.config.json  # アプリ設定（エントリポイント・ウィンドウ設定）
└── resources/              # HTML・CSS・JS によるフロントエンド UI
```
