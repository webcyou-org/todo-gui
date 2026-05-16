# remi Todo

Python Todo app using [remi](https://github.com/rawpython/remi) — browser-based GUI toolkit.

アプリ起動後、ブラウザで `http://localhost:8080` を開いてください。

## Requirements

- Python 3.9+

## Install

```sh
pip install remi
```

## Run

```sh
python main.py
```

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