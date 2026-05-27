# wxPython Todo

Python Todo app using [wxPython](https://wxpython.org/) — wxWidgets bindings for Python.

## Requirements

- Python 3.9+

Python is available on all platforms. Install from https://python.org or:
- macOS: `brew install python3`
- Windows: `winget install Python.Python.3`
- Linux: usually pre-installed; `sudo apt install python3 python3-pip`

## Install

**macOS**
```sh
pip install wxPython
```

If installation fails on macOS, specify the wheel explicitly:
```sh
pip install -U -f https://extras.wxpython.org/wxPython4/extras/macosx/cocoa wxPython
```

**Windows**
```sh
pip install wxPython
```

**Linux (Ubuntu/Debian)**
```sh
sudo apt install libwx-gtk3u-dev
pip install wxPython
```
Or download a pre-built wheel from https://extras.wxpython.org/wxPython4/extras/linux/

## Run

```sh
python main.py
```

> Windows: use `python` instead of `python3` if needed.

## Architecture

A wx.Frame-based structure using wxPython. Data model and widget components are separated into files; `main.py` constructs the main window.

```
.
├── main.py         # entry point · wx.App · main window construction
├── data.py         # Todo data model · TabFilter · state management
├── theme.py        # color and style constants
└── widgets/        # wxPython widget components for tabs, input, and Todo rows
```