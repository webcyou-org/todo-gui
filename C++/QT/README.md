# Qt Todo

C++ Todo app using [Qt5](https://www.qt.io/) Widgets.

## Requirements

- Qt5 (`qtbase`)
- qmake (bundled with Qt5)

## Install

**macOS**
```sh
brew install qt@5
export PATH="/opt/homebrew/opt/qt@5/bin:$PATH"
```

**Windows**
Download Qt Installer from https://www.qt.io/download or `winget install Qt.Qt.6`

**Linux (Ubuntu/Debian)**
```sh
sudo apt install qt6-base-dev cmake
```

## Build

```sh
qmake QT.pro
make
```

## Run

```sh
open QT.app
```

## Architecture

MVC pattern using Qt5 Widgets. The data model is implemented by subclassing `QAbstractListModel`, and the UI is rendered using custom widgets.

| Layer | File | Role |
|-------|------|------|
| Model | `data.h`, `todomodel.h/cpp` | Todo data · QAbstractListModel implementation |
| View | `mainwindow.h/cpp`, `todoitemwidget.h/cpp` | Qt Widgets UI · custom row widget |
| Entry | `main.cpp` | QApplication startup · MainWindow creation |
| Theme | `theme.h` | color and style constants |