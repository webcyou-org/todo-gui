# PyGTK (PyGObject) Todo

Python Todo app using [PyGObject](https://pygobject.gnome.org/) (GTK3 bindings for Python).

## Requirements

- Python 3.9+
- GTK3
- gobject-introspection

```sh
brew install gtk+3 gobject-introspection pygobject3
```

## Install

```sh
pip install PyGObject
```

## Run

```sh
python main.py
```

## Architecture

PyGObject（GTK3 バインディング）を使ったシングルパッケージ構成。データモデルとウィジェット部品をファイルで分離し、`main.py` がウィンドウを構築する。

```
.
├── main.py         # エントリーポイント・Gtk.Application・ウィンドウ構築
├── data.py         # Todo データモデル・TabFilter・状態管理
├── theme.py        # カラー・CSS 定数
└── widgets/        # 入力欄・タブ・リストの GTK3 ウィジェット部品
```