# Carlo Todo

Node.js Todo app using [Carlo](https://github.com/GoogleChromeLabs/carlo) — HTML/CSS UI over Chrome via Node.js.

> Carlo uses Chrome/Chromium as its runtime.

## Requirements

- Node.js 18+
- Google Chrome installed

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

A two-layer structure with a Node.js backend and an HTML/CSS/JS frontend. Carlo launches a Chrome window and provides a bridge so that Node.js functions can be called from the frontend.

```
.
├── index.js        # entry point · Carlo window launch · Node.js function binding
├── index.html      # frontend HTML
└── style.css       # frontend styles
```