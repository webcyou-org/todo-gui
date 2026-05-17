# Toga Todo

Python Todo app using [Toga](https://toga.readthedocs.io/) — BeeWare's native GUI toolkit.

## Requirements

- Python 3.9+

**macOS** (requires Xcode):
```sh
pip install toga[cocoa]
```

**Windows**
```sh
pip install toga[winforms]
```

**Linux (Ubuntu/Debian)**
```sh
sudo apt install python3 python3-pip python3-gi python3-gi-cairo gir1.2-gtk-3.0
pip install toga[gtk]
```

## Run

```sh
python main.py
```

> Windows: use `python` instead of `python3` if needed.

## Architecture

Toga の BeeWare 宣言的ウィジェット構成。データモデルとウィジェット部品をファイルで分離し、`main.py` がアプリを起動する。

```
.
├── main.py         # エントリーポイント・toga.App・メインウィンドウ構築
├── data.py         # Todo データモデル・TabFilter・状態管理
├── theme.py        # カラー・スタイル定数
└── widgets/        # 入力欄・タブ・Todo 行の Toga ウィジェット部品
```