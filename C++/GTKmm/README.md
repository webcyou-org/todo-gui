# GTKmm Todo

C++ Todo app using [gtkmm](https://gtkmm.org/) 3 (C++ wrappers for GTK).

## Requirements

- CMake 3.15+
- gtkmm-3.0
- pkg-config

## Install

**macOS**
```sh
brew install cmake gtkmm3 pkg-config
```

**Windows**
```sh
winget install Kitware.CMake
```
Install gtkmm via MSYS2: `pacman -S mingw-w64-x86_64-gtkmm4`

**Linux (Ubuntu/Debian)**
```sh
sudo apt install cmake build-essential libgtkmm-3.0-dev pkg-config
```

## Build

```sh
cmake -B build
cmake --build build
```

## Run

```sh
./build/main
```

## Architecture

An object-oriented structure that inherits and composes gtkmm C++ widget classes. Data model and widget components are separated into files.

```
src/
├── main.cpp        # entry point · Gtk::Application · window construction
├── data.h          # Todo data model · AppState · TabFilter
├── theme.h         # color constants · design tokens
├── cairo_util.h    # Cairo drawing utilities
└── widgets/        # widget components for input (todo_input) · tabs (tab_menu) · list (todo_list)
```