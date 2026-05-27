# GTK4 Todo

C++ Todo app using [GTK4](https://gtk.org/).

## Requirements

- clang++
- GTK4
- pkg-config

## Install

**macOS**
```sh
brew install gtk4 pkg-config
```

**Windows**
Install GTK4 via MSYS2: `pacman -S mingw-w64-x86_64-gtk4`

**Linux (Ubuntu/Debian)**
```sh
sudo apt install libgtk-4-dev pkg-config
```

## Build

```sh
make
```

## Run

```sh
./todo
```

## Architecture

A single-binary structure that directly uses the GTK4 C API. Data model and widget construction are separated into files, with custom drawing performed via Cairo.

```
src/
├── main.cpp        # entry point · GtkApplication · window construction
├── data.h          # Todo data model · AppState · TabFilter
├── app.h           # application state · widget references
├── theme.h         # color constants · design tokens
├── cairo_util.h    # Cairo drawing utilities
└── widgets/        # GTK4 widget components for input, tabs, and list
```