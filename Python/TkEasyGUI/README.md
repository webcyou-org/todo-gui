# TkEasyGUI Todo

Python Todo app using [TkEasyGUI](https://github.com/kujirahand/tkeasygui-python) — simplified Tkinter wrapper.

## Requirements

- Python 3.9+
- Tcl/Tk (bundled with Python)

Python is available on all platforms. Install from https://python.org or:
- macOS: `brew install python3` (Tcl/Tk bundled)
- Windows: `winget install Python.Python.3` (Tcl/Tk bundled)
- Linux: `sudo apt install python3 python3-pip python3-tk`

## Install

Works on all platforms:
```sh
pip install TkEasyGUI
```

## Run

```sh
python main.py
```

> Windows: use `python` instead of `python3` if needed.

## Architecture

An event-driven loop structure using TkEasyGUI. `main.py` defines the window layout and handles events, in a simple near-single-file structure.

```
.
├── main.py         # entry point · window layout · event loop
├── data.py         # Todo data model · TabFilter · state management
└── theme.py        # color and style constants
```