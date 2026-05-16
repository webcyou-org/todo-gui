# wxPython Todo

Python Todo app using [wxPython](https://wxpython.org/) — wxWidgets bindings for Python.

## Requirements

- Python 3.9+

## Install

```sh
pip install wxPython
```

macOS でインストールに失敗する場合は wheel を指定してください:

```sh
pip install -U -f https://extras.wxpython.org/wxPython4/extras/macosx/cocoa wxPython
```

## Run

```sh
python main.py
```

## Architecture

wxPython の wx.Frame ベース構成。データモデルとウィジェット部品をファイルで分離し、`main.py` がメインウィンドウを構築する。

```
.
├── main.py         # エントリーポイント・wx.App・メインウィンドウ構築
├── data.py         # Todo データモデル・TabFilter・状態管理
├── theme.py        # カラー・スタイル定数
└── widgets/        # タブ・入力欄・Todo 行の wxPython ウィジェット部品
```