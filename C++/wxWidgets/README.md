# wxWidgets Todo

C++ Todo app using [wxWidgets](https://www.wxwidgets.org/).  
wxWidgets itself is built from source via CMake ExternalProject (`thirdparty/wxwidgets/`).

## Requirements

- CMake 3.6+
- pkg-config
- macOS: Xcode Command Line Tools

## Install

**macOS**
```sh
xcode-select --install
brew install cmake pkg-config
```

**Windows**
```sh
winget install Kitware.CMake
```
wxWidgets is built from source (bundled via CMake ExternalProject — no separate install needed).

**Linux (Ubuntu/Debian)**
```sh
sudo apt install cmake build-essential pkg-config libgtk-3-dev
```
wxWidgets is built from source (bundled via CMake ExternalProject — no separate install needed).

## Build

The first build takes several minutes as it includes compiling wxWidgets.

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

## Run

```sh
./build/subprojects/Build/todo_core/todo
```

## Architecture

Pure C++ implementation. An event-driven UI is built by inheriting and composing wxWidgets widgets, with data model and widget components separated into files. The wxWidgets library itself is built from source via CMake ExternalProject.

```
src/
├── main.cpp        # entry point · wxApp · main window construction
├── data.h          # Todo data model · AppState · TabFilter
├── theme.h         # color and style constants
└── widgets/        # wxWidgets widget components for input, tabs, and list
thirdparty/wxwidgets/   # wxWidgets source (CMake ExternalProject)
```