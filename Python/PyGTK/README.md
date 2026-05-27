# PyGTK (PyGObject) Todo

Python Todo app using [PyGObject](https://pygobject.gnome.org/) (GTK3 bindings for Python).

## Requirements

- Python 3.9+
- GTK3
- gobject-introspection

**macOS**
```sh
brew install gtk+3 gobject-introspection pygobject3
```

**Windows**
Install via MSYS2: `pacman -S mingw-w64-x86_64-python-gobject mingw-w64-x86_64-gtk3`

**Linux (Ubuntu/Debian)**
```sh
sudo apt install python3-gi python3-gi-cairo gir1.2-gtk-3.0 libgtk-3-dev gobject-introspection
```

## Install

```sh
pip install PyGObject
```

## Run

```sh
python main.py
```

> Windows: use `python` instead of `python3` if needed.

## Architecture

A single-package structure using PyGObject (GTK3 bindings). Data model and widget components are separated into files; `main.py` constructs the window.

```
.
├── main.py         # entry point · Gtk.Application · window construction
├── data.py         # Todo data model · TabFilter · state management
├── theme.py        # color and CSS constants
└── widgets/        # GTK3 widget components for input, tabs, and list
```