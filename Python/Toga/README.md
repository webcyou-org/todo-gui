# Toga Todo

Python Todo app using [Toga](https://toga.readthedocs.io/) — BeeWare's native GUI toolkit.

## Requirements

- Python 3.9+
- macOS: Xcode インストール済み

## Install

```sh
pip install toga[cocoa]
```

## Run

```sh
python main.py
```

## Architecture

Toga の BeeWare 宣言的ウィジェット構成。データモデルとウィジェット部品をファイルで分離し、`main.py` がアプリを起動する。

```
.
├── main.py         # エントリーポイント・toga.App・メインウィンドウ構築
├── data.py         # Todo データモデル・TabFilter・状態管理
├── theme.py        # カラー・スタイル定数
└── widgets/        # 入力欄・タブ・Todo 行の Toga ウィジェット部品
```