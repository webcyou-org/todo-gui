# Flet Todo

Python Todo app using [Flet](https://flet.dev/) — Flutter-based UI for Python.

## Requirements

- Python 3.9+

Python is available on all platforms. Install from https://python.org or:
- macOS: `brew install python3`
- Windows: `winget install Python.Python.3`
- Linux: usually pre-installed; `sudo apt install python3 python3-pip`

## Install

Works on all platforms:
```sh
pip install flet
```

## Run

```sh
python main.py
```

> Windows: use `python` instead of `python3` if needed.

## Architecture

A near-single-file declarative Flutter-based UI using Flet. Data model and components are separated into files; `main.py` constructs the page.

```
.
├── main.py         # entry point · flet.app · page construction
├── data.py         # Todo data model · TabFilter · state management
├── theme.py        # color and style constants
└── components/     # Flet components for input, tabs, and list
```