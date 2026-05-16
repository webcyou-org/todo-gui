# PySide6 Todo

Python Todo app using [PySide6](https://doc.qt.io/qtforpython/) — official Qt6 bindings for Python.

## Requirements

- Python 3.9+

## Install

```sh
pip install PySide6
```

## Run

```sh
python main.py
```

## Architecture

PySide6 の Qt6 Widgets を直接組み立てるシングルパッケージ構成。データモデルとコンポーネントをファイルで分離し、`main.py` がメインウィンドウを構築する。

```
.
├── main.py         # エントリーポイント・QApplication・ウィンドウ構築
├── data.py         # Todo データモデル・TabFilter・状態管理
├── theme.py        # カラー・スタイル定数
└── components/     # 入力欄・タブ・リストの Qt6 ウィジェット部品
```