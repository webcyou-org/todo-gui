# PyForms Todo

Python Todo app using [PyForms](https://pyforms.readthedocs.io/) with PyQt5 backend.

## Requirements

- Python 3.9+

Python is available on all platforms. Install from https://python.org or:
- macOS: `brew install python3`
- Windows: `winget install Python.Python.3`
- Linux: usually pre-installed; `sudo apt install python3 python3-pip`

## Install

Works on all platforms:
```sh
pip install PyQt5 pyforms-gui
```

## Run

```sh
python main.py
```

> Windows: use `python` instead of `python3` if needed.

## Architecture

A form-based structure using PyForms. A form class inheriting `BaseWidget` integrates UI and logic, with the PyQt5 backend rendering the widgets.

```
.
├── main.py         # entry point · PyForms app launch · TodoForm definition
├── data.py         # Todo data model · TabFilter · state management
└── theme.py        # color and style constants
```