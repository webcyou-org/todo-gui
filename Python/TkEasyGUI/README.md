# TkEasyGUI Todo

Python Todo app using [TkEasyGUI](https://github.com/kujirahand/tkeasygui-python) — simplified Tkinter wrapper.

## Requirements

- Python 3.9+
- Tcl/Tk（Python に同梱）

Python is available on all platforms. Install from https://python.org or:
- macOS: `brew install python3` (Tcl/Tk bundled)
- Windows: `winget install Python.Python.3` (Tcl/Tk bundled)
- Linux: `sudo apt install python3 python3-pip python3-tk`

## Install

Works on all platforms:
```sh
pip install TkEasyGUI
```

## Run

```sh
python main.py
```

> Windows: use `python` instead of `python3` if needed.

## Architecture

TkEasyGUI のイベント駆動ループ構成。`main.py` がウィンドウレイアウトを定義しイベントを処理する、シンプルなシングルファイルに近い構成。

```
.
├── main.py         # エントリーポイント・ウィンドウレイアウト・イベントループ
├── data.py         # Todo データモデル・TabFilter・状態管理
└── theme.py        # カラー・スタイル定数
```