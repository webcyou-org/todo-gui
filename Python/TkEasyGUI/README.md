# TkEasyGUI Todo

Python Todo app using [TkEasyGUI](https://github.com/kujirahand/tkeasygui-python) — simplified Tkinter wrapper.

## Requirements

- Python 3.9+
- Tcl/Tk（macOS では Python インストール時に同梱）

## Install

```sh
pip install TkEasyGUI
```

## Run

```sh
python main.py
```

## Architecture

TkEasyGUI のイベント駆動ループ構成。`main.py` がウィンドウレイアウトを定義しイベントを処理する、シンプルなシングルファイルに近い構成。

```
.
├── main.py         # エントリーポイント・ウィンドウレイアウト・イベントループ
├── data.py         # Todo データモデル・TabFilter・状態管理
└── theme.py        # カラー・スタイル定数
```