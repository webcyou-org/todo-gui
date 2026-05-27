# U++ Todo

C++ Todo app using [U++ (Ultimate++)](https://www.ultimatepp.org/).

## Requirements

- U++ framework (umk build tool + uppsrc)
- macOS / Linux / Windows (via MSYS2)

> Windows: Please use the MSYS2 environment (https://www.msys2.org/).

## Install

Obtain the source from the [U++ official website](https://www.ultimatepp.org/www$uppweb$download$en-us.html) and extract it under `/tmp/ultimatepp/`.

```sh
# Get source (example)
git clone https://github.com/ultimatepp/ultimatepp /tmp/ultimatepp
cd /tmp/ultimatepp
# Build umk
cd uppsrc/umk && make
```

For details, refer to the [U++ on Linux/macOS guide](https://www.ultimatepp.org/app$ide$install$en-us.html).

Check environment variables (see Makefile):

```sh
# Default values
UMK   = /tmp/ultimatepp/umk
UPPSRC = /tmp/ultimatepp/uppsrc
```

## Build & Run

```sh
make build
make run
```

## Architecture

A single-package structure using U++ IDE layout description (`.upp`). Data model and widget components are separated into files.

```
TodoApp/
├── main.cpp        # entry point · TopWindow construction · event handling
├── data.h/cpp      # Todo data model · AppState · TabFilter
├── theme.h         # color and style constants
├── TodoApp.upp     # U++ package definition
└── widgets/        # U++ widget components for input, tabs, and list
```