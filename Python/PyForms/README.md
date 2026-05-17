# PyForms Todo

Python Todo app using [PyForms](https://pyforms.readthedocs.io/) with PyQt5 backend.

## Requirements

- Python 3.9+

Python is available on all platforms. Install from https://python.org or:
- macOS: `brew install python3`
- Windows: `winget install Python.Python.3`
- Linux: usually pre-installed; `sudo apt install python3 python3-pip`

## Install

Works on all platforms:
```sh
pip install PyQt5 pyforms-gui
```

## Run

```sh
python main.py
```

> Windows: use `python` instead of `python3` if needed.

## Architecture

PyForms のフォームベース構成。`BaseWidget` を継承したフォームクラスが UI とロジックを統合し、PyQt5 バックエンドでウィジェットをレンダリングする。

```
.
├── main.py         # エントリーポイント・PyForms アプリ起動・TodoForm 定義
├── data.py         # Todo データモデル・TabFilter・状態管理
└── theme.py        # カラー・スタイル定数
```