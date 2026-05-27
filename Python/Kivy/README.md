# Kivy Todo

Python Todo app using [Kivy](https://kivy.org/) — cross-platform GUI framework.

## Requirements

- Python 3.9+

Python is available on all platforms. Install from https://python.org or:
- macOS: `brew install python3`
- Windows: `winget install Python.Python.3`
- Linux: usually pre-installed; `sudo apt install python3 python3-pip`

## Install

Works on all platforms:
```sh
pip install kivy
```

If you see OpenGL warnings on macOS:

```sh
pip install kivy[base]
```

## Run

```sh
python main.py
```

> Windows: use `python` instead of `python3` if needed.

## Architecture

A declarative UI structure using Kivy's widget tree. Data model and components are separated into files; `main.py` launches the app.

```
.
├── main.py         # entry point · App class · root widget construction
├── data.py         # Todo data model · TabFilter · state management
├── theme.py        # color and font constants
└── components/     # Kivy widget components for input, tabs, and list
```