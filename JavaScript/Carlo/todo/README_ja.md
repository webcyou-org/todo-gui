# Carlo Todo

Node.js Todo app using [Carlo](https://github.com/GoogleChromeLabs/carlo) — HTML/CSS UI over Chrome via Node.js.

> Carlo は Chrome/Chromium をランタイムとして使用します。

## Requirements

- Node.js 18+
- Google Chrome インストール済み

**macOS**
```sh
brew install node
brew install --cask google-chrome
```

**Windows**
```sh
winget install OpenJS.NodeJS Google.Chrome
```

**Linux (Ubuntu/Debian)**
```sh
sudo apt install nodejs npm
```
Install Chrome from https://www.google.com/chrome/

## Install

```sh
npm install
```

## Run

```sh
node index.js
```

## Architecture

Node.js バックエンドと HTML/CSS/JS フロントエンドの 2 層構成。Carlo が Chrome ウィンドウを起動し、Node.js の関数をフロントエンドから呼び出せるよう bridge を提供する。

```
.
├── index.js        # エントリーポイント・Carlo ウィンドウ起動・Go 関数バインド
├── index.html      # フロントエンド HTML
└── style.css       # フロントエンドスタイル
```