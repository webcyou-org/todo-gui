# remi Todo

Python Todo app using [remi](https://github.com/rawpython/remi) — browser-based GUI toolkit.

アプリ起動後、ブラウザで `http://localhost:8080` を開いてください。

## Requirements

- Python 3.9+

Python is available on all platforms. Install from https://python.org or:
- macOS: `brew install python3`
- Windows: `winget install Python.Python.3`
- Linux: usually pre-installed; `sudo apt install python3 python3-pip`

## Install

Works on all platforms:
```sh
pip install remi
```

## Run

```sh
python main.py
```

> Windows: use `python` instead of `python3` if needed.

ブラウザが自動的に起動します。起動しない場合は `http://localhost:8080` にアクセスしてください。

## Architecture

remi のブラウザ WebSocket ベース構成。Python でウィジェットを定義すると remi が HTML に変換し、ブラウザ（または組み込み WebView）で表示する。状態とロジックはすべてサーバーサイド Python で管理する。

```
.
├── main.py         # エントリーポイント・remi.start・App クラス・ウィジェット定義
├── data.py         # Todo データモデル・TabFilter・状態管理
├── theme.py        # カラー・CSS 定数
└── widgets/        # 入力欄・タブ・リストの remi ウィジェット部品
```