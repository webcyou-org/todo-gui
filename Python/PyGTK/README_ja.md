# PyGTK (PyGObject) Todo

Python Todo app using [PyGObject](https://pygobject.gnome.org/) (GTK3 bindings for Python).

## Requirements

- Python 3.9+
- GTK3
- gobject-introspection

**macOS**
```sh
brew install gtk+3 gobject-introspection pygobject3
```

**Windows**
Install via MSYS2: `pacman -S mingw-w64-x86_64-python-gobject mingw-w64-x86_64-gtk3`

**Linux (Ubuntu/Debian)**
```sh
sudo apt install python3-gi python3-gi-cairo gir1.2-gtk-3.0 libgtk-3-dev gobject-introspection
```

## Install

```sh
pip install PyGObject
```

## Run

```sh
python main.py
```

> Windows: use `python` instead of `python3` if needed.

## Architecture

PyGObject（GTK3 バインディング）を使ったシングルパッケージ構成。データモデルとウィジェット部品をファイルで分離し、`main.py` がウィンドウを構築する。

```
.
├── main.py         # エントリーポイント・Gtk.Application・ウィンドウ構築
├── data.py         # Todo データモデル・TabFilter・状態管理
├── theme.py        # カラー・CSS 定数
└── widgets/        # 入力欄・タブ・リストの GTK3 ウィジェット部品
```