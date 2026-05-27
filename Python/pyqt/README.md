# PyQt6 Todo

Python Todo app using [PyQt6](https://www.riverbankcomputing.com/software/pyqt/) — Qt6 bindings for Python.

## Requirements

- Python 3.9+

Python is available on all platforms. Install from https://python.org or:
- macOS: `brew install python3`
- Windows: `winget install Python.Python.3`
- Linux: usually pre-installed; `sudo apt install python3 python3-pip`

## Install

Works on all platforms:
```sh
pip install PyQt6
```

## Run

```sh
python main.py
```

> Windows: use `python` instead of `python3` if needed.

## Architecture

A single-package structure that assembles Qt6 Widgets directly via PyQt6. Data model and components are separated into files; `main.py` constructs the main window.

```
.
├── main.py         # entry point · QApplication · window construction
├── data.py         # Todo data model · TabFilter · state management
├── theme.py        # color and style constants
└── components/     # Qt6 widget components for tab menu, input, and Todo list
```