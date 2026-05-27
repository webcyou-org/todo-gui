# raylib Todo

C++ Todo app using [raylib](https://www.raylib.com/).

## Requirements

- clang++
- raylib 5.5
- pkg-config

## Install

**macOS**
```sh
brew install raylib pkg-config
```

**Windows**
Download raylib from https://github.com/raysan5/raylib/releases or `winget install raysan5.raylib`

**Linux (Ubuntu/Debian)**
```sh
sudo apt install libraylib-dev pkg-config
```
For raylib 5.5, build from source: https://github.com/raysan5/raylib

## Build

```sh
make
```

## Run

```sh
./todo
```

## Architecture

Immediate Mode drawing pattern. The UI is drawn every frame within raylib's frame loop, and state is centrally managed in an `AppState` struct.

```
src/
├── main.cpp        # entry point · window initialization · main loop
├── data.h          # AppState · Todo · TabFilter
├── theme.h         # color and font constants
├── draw_helpers.h  # drawing utilities such as rounded rectangles
└── components/     # drawing components for input, tabs, and list
```