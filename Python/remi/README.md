# remi Todo

Python Todo app using [remi](https://github.com/rawpython/remi) — browser-based GUI toolkit.

After launching the app, open `http://localhost:8080` in your browser.

## Requirements

- Python 3.9+

Python is available on all platforms. Install from https://python.org or:
- macOS: `brew install python3`
- Windows: `winget install Python.Python.3`
- Linux: usually pre-installed; `sudo apt install python3 python3-pip`

## Install

Works on all platforms:
```sh
pip install remi
```

## Run

```sh
python main.py
```

> Windows: use `python` instead of `python3` if needed.

The browser opens automatically. If it doesn't, navigate to `http://localhost:8080`.

## Architecture

A browser WebSocket-based structure using remi. Widgets defined in Python are converted to HTML by remi and displayed in a browser (or embedded WebView). All state and logic are managed server-side in Python.

```
.
├── main.py         # entry point · remi.start · App class · widget definitions
├── data.py         # Todo data model · TabFilter · state management
├── theme.py        # color and CSS constants
└── widgets/        # remi widget components for input, tabs, and list
```