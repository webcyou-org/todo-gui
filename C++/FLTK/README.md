# FLTK Todo

C++ Todo app using [FLTK](https://www.fltk.org/) (Fast Light Toolkit).

## Requirements

- CMake 3.15+
- FLTK

## Install

**macOS**
```sh
brew install cmake fltk
```

**Windows**
```sh
winget install Kitware.CMake
```
Download FLTK from https://www.fltk.org/software.php or `winget install FLTK.FLTK`

**Linux (Ubuntu/Debian)**
```sh
sudo apt install cmake build-essential libfltk1.3-dev
```

## Build

```sh
cmake -B build
cmake --build build
```

## Run

```sh
open build/main.app
```

> Building on macOS produces a `.app` bundle.

## Architecture

A near-single-file simple structure. FLTK widgets are assembled directly, with data and logic managed together in a C++ class.

```
src/
├── main.cpp        # entry point · window construction · event loop
├── data.h          # Todo data model · AppState · TabFilter
├── theme.h         # color constants · design tokens
└── widgets/        # FLTK widget components for input, tabs, and list
```