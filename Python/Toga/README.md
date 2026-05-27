# Toga Todo

Python Todo app using [Toga](https://toga.readthedocs.io/) — BeeWare's native GUI toolkit.

## Requirements

- Python 3.9+

**macOS** (requires Xcode):
```sh
pip install toga[cocoa]
```

**Windows**
```sh
pip install toga[winforms]
```

**Linux (Ubuntu/Debian)**
```sh
sudo apt install python3 python3-pip python3-gi python3-gi-cairo gir1.2-gtk-3.0
pip install toga[gtk]
```

## Run

```sh
python main.py
```

> Windows: use `python` instead of `python3` if needed.

## Architecture

A declarative widget structure using Toga's BeeWare framework. Data model and widget components are separated into files; `main.py` launches the app.

```
.
├── main.py         # entry point · toga.App · main window construction
├── data.py         # Todo data model · TabFilter · state management
├── theme.py        # color and style constants
└── widgets/        # Toga widget components for input, tabs, and Todo rows
```