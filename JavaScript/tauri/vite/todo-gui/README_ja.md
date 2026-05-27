# Tauri + Vue Todo

JavaScript/Vue3 Todo app using [Tauri](https://tauri.app/) v1 with Vite — lightweight desktop app framework.

## Requirements

- Node.js 18+
- Rust (stable)

**macOS** (requires Xcode Command Line Tools):
```sh
xcode-select --install
brew install node
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

**Windows**
```sh
winget install OpenJS.NodeJS Rustlang.Rustup
```
Also install [Microsoft C++ Build Tools](https://visualstudio.microsoft.com/visual-cpp-build-tools/) (required by Rust/Tauri).

**Linux (Ubuntu/Debian)**
```sh
sudo apt install nodejs npm curl build-essential libwebkit2gtk-4.1-dev libssl-dev
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

```sh
# Tauri CLI
npm install -g @tauri-apps/cli
```

## Install

```sh
npm install
```

## Run（開発モード）

```sh
npm run tauri dev
```

## Build（本番バイナリ）

```sh
npm run tauri build
```

## Architecture

Rust バックエンド（Tauri）と Vue3 フロントエンド（Vite）の 2 層構成。Tauri が軽量ネイティブシェルと IPC を提供し、フロントエンドはシステム WebView で表示される。

```
.
├── src/            # Vue3 + Vite フロントエンド（App.vue・コンポーネント）
└── src-tauri/      # Rust バックエンド（Tauri 設定・ネイティブコマンド定義）
    └── tauri.conf.json  # ウィンドウ設定・権限定義
```
