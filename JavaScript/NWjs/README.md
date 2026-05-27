# NW.js Todo

JavaScript Todo app using [NW.js](https://nwjs.io/) (formerly node-webkit).

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
npm run dev
```

> The app entry point (`main`) and window configuration are defined in `src/package.json`.

## Architecture

An NW.js Node.js-integrated browser window structure. The entry point and window configuration are defined in `src/package.json`, and the UI is implemented in HTML/CSS/JS.

```
src/
├── package.json    # NW.js app configuration (main, window size, etc.)
├── views/          # HTML pages
├── styles/         # CSS stylesheets
└── app/            # JavaScript app logic
```