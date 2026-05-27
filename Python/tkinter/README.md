# tkinter Todo

Python Todo app using [tkinter](https://docs.python.org/3/library/tkinter.html) — Python's standard GUI library.

## Requirements

- Python 3.9+
- Tcl/Tk (bundled with Python)

Python is available on all platforms:
- macOS: `brew install python3` (Tcl/Tk bundled)
- Windows: `winget install Python.Python.3` (Tcl/Tk bundled)
- Linux: `sudo apt install python3 python3-tk`

## Run

**macOS / Linux**
```bash
python3 main.py
```

**Windows**
```bash
python main.py
```

### If tkinter doesn't work on macOS

Python installed via pyenv may not have tkinter due to a dependency issue with tcl-tk.  
Install Python and tkinter separately via Homebrew and run from there.

```bash
brew install python-tk@3.9
python3.9 main.py
```

## File Structure

```
tkinter/
├── main.py               # entry point · root window
├── data.py               # data model (Todo, TodoModel, MenuModel)
├── theme.py              # color constants · font · drawing utilities
└── components/
    ├── todo_input.py     # input field
    ├── tabs.py           # tab menu (All / Active / Completed)
    └── todo_list.py      # Todo list (scroll-enabled)
```

## Architecture

A structure combining tkinter Canvas-based drawing with native widgets. Data model and components are separated into files; `main.py` constructs the root window.

| Layer | File | Role |
|-------|------|------|
| Model | `data.py` | Todo · TodoModel · MenuModel · state management |
| View | `components/` | tkinter widget components for input, tabs, and list |
| Entry | `main.py` | Tk root window construction · layout |
| Theme | `theme.py` | color constants · font · drawing utilities |