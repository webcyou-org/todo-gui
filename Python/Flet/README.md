# Flet Todo

Python Todo app using [Flet](https://flet.dev/) — Flutter-based UI for Python.

## Requirements

- Python 3.9+

Python is available on all platforms. Install from https://python.org or:
- macOS: `brew install python3`
- Windows: `winget install Python.Python.3`
- Linux: usually pre-installed; `sudo apt install python3 python3-pip`

## Install

Works on all platforms:
```sh
pip install flet
```

## Run

```sh
python main.py
```

> Windows: use `python` instead of `python3` if needed.

## Architecture

Flet の宣言的 Flutter ベース UI をシングルファイルに近い構成で実装。データモデルとコンポーネントをファイルで分離し、`main.py` がページを構築する。

```
.
├── main.py         # エントリーポイント・flet.app・ページ構築
├── data.py         # Todo データモデル・TabFilter・状態管理
├── theme.py        # カラー・スタイル定数
└── components/     # 入力欄・タブ・リストの Flet コンポーネント
```