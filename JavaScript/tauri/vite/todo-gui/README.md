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

## Run (development mode)

```sh
npm run tauri dev
```

## Build (production binary)

```sh
npm run tauri build
```

## Architecture

A two-layer structure with a Rust backend (Tauri) and a Vue3 frontend (Vite). Tauri provides a lightweight native shell and IPC, with the frontend displayed via the system WebView.

```
.
├── src/            # Vue3 + Vite frontend (App.vue · components)
└── src-tauri/      # Rust backend (Tauri configuration · native command definitions)
    └── tauri.conf.json  # window configuration · permission definitions
```