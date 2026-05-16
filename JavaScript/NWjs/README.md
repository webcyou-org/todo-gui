# NW.js Todo

JavaScript Todo app using [NW.js](https://nwjs.io/) (formerly node-webkit).

## Requirements

- Node.js 18+

## Install

```sh
npm install
```

## Run

```sh
npm run dev
```

> `src/package.json` でアプリのエントリポイント（`main`）とウィンドウ設定が定義されています。

## Architecture

NW.js の Node.js 統合ブラウザウィンドウ構成。`src/package.json` でエントリポイントとウィンドウ設定を定義し、HTML/CSS/JS で UI を実装する。

```
src/
├── package.json    # NW.js アプリ設定（main・ウィンドウサイズ等）
├── views/          # HTML ページ
├── styles/         # CSS スタイルシート
└── app/            # JavaScript アプリロジック
```