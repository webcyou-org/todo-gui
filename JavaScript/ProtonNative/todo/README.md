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

A single-file structure that manipulates native widgets using React-like declarative syntax. `app.js` defines the component tree, and ProtonNative maps it to native UI.

```
.
├── index.js        # entry point · ProtonNative App launch
└── app.js          # UI definition and state management via React-like components
```