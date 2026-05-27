# ProtonNative Todo

JavaScript Todo app using [ProtonNative](https://proton-native.js.org/) — React-like syntax for native desktop apps.

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

React ライクな宣言的構文でネイティブウィジェットを操作するシングルファイル構成。`app.js` がコンポーネントツリーを定義し、ProtonNative がネイティブ UI にマッピングする。

```
.
├── index.js        # エントリーポイント・ProtonNative App 起動
└── app.js          # React ライクコンポーネントによる UI 定義・状態管理
```