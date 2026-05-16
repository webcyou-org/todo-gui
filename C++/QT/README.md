# Qt Todo

C++ Todo app using [Qt5](https://www.qt.io/) Widgets.

## Requirements

- Qt5 (`qtbase`)
- qmake (bundled with Qt5)

## Install

```sh
brew install qt@5
export PATH="/opt/homebrew/opt/qt@5/bin:$PATH"
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

Qt5 Widgets の MVC パターン。`QAbstractListModel` をサブクラス化してデータモデルを実装し、カスタムウィジェットで UI を描画する。

| レイヤー | ファイル | 役割 |
|---------|---------|------|
| Model | `data.h`, `todomodel.h/cpp` | Todo データ・QAbstractListModel 実装 |
| View | `mainwindow.h/cpp`, `todoitemwidget.h/cpp` | Qt Widgets UI・カスタム行ウィジェット |
| Entry | `main.cpp` | QApplication 起動・MainWindow 生成 |
| Theme | `theme.h` | カラー・スタイル定数 |