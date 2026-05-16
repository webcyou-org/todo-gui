# Wails Todo

Go + Vue3 Todo app using [Wails](https://wails.io/) v2 — build desktop apps with Go backend and web frontend.

## Requirements

- Go 1.21+
- Node.js 18+
- Wails CLI

```sh
go install github.com/wailsapp/wails/v2/cmd/wails@latest
```

macOS は Xcode Command Line Tools が必要:

```sh
xcode-select --install
```

## Install

```sh
wails doctor   # 環境チェック
```

## Run（開発モード）

```sh
wails dev
```

フロントエンドの変更はホットリロードされます。Go コードは `http://localhost:34115` のブラウザ devtools からも呼び出せます。

## Build（配布バイナリ）

```sh
wails build
# 出力先: build/bin/
```

## Architecture

Go バックエンドと Vue3 フロントエンドの 2 層構成。Wails が IPC ブリッジを提供し、フロントエンドから Go のメソッドを透過的に呼び出せる。

```
.
├── main.go         # エントリーポイント・Wails アプリ起動
├── app.go          # Go バックエンド（Todo CRUD メソッド・状態管理）
├── frontend/       # Vue3 + Vite によるフロントエンド UI
│   └── src/        # App.vue・コンポーネント・スタイル
└── wailsjs/        # Wails が自動生成した Go→JS バインディング
```
