# Reflex Todo

Python Todo app using [Reflex](https://reflex.dev/) — full-stack web framework in pure Python.

## Requirements

- Python 3.9+
- Node.js 18+ (used for Reflex's frontend build)

Python and Node.js are available on all platforms:
- macOS: `brew install python3 node`
- Windows: `winget install Python.Python.3 OpenJS.NodeJS`
- Linux: `sudo apt install python3 python3-pip nodejs npm`

## Install

```sh
pip install reflex
```

## Initialize (first time only)

```sh
reflex init
```

## Run

```sh
reflex run
```

The browser opens `http://localhost:3000` automatically.

## Architecture

A full-stack Python structure using Reflex. State management and event handlers are defined as server-side Python classes; Reflex automatically compiles the frontend to React.

```
todo/
├── todo.py         # root page · UI definition · State class (state management · CRUD)
├── rxconfig.py     # Reflex app configuration
└── assets/         # static assets
```