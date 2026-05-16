# PyQt6 Todo

Python Todo app using [PyQt6](https://www.riverbankcomputing.com/software/pyqt/) — Qt6 bindings for Python.

## Requirements

- Python 3.9+

## Install

```sh
pip install PyQt6
```

## Run

```sh
python main.py
```

## Architecture

PyQt6 の Qt6 Widgets を直接組み立てるシングルパッケージ構成。データモデルとコンポーネントをファイルで分離し、`main.py` がメインウィンドウを構築する。

```
.
├── main.py         # エントリーポイント・QApplication・ウィンドウ構築
├── data.py         # Todo データモデル・TabFilter・状態管理
├── theme.py        # カラー・スタイル定数
└── components/     # タブメニュー・入力欄・Todo リストの Qt6 ウィジェット部品
```