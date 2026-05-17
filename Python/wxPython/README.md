# wxPython Todo

Python Todo app using [wxPython](https://wxpython.org/) — wxWidgets bindings for Python.

## Requirements

- Python 3.9+

Python is available on all platforms. Install from https://python.org or:
- macOS: `brew install python3`
- Windows: `winget install Python.Python.3`
- Linux: usually pre-installed; `sudo apt install python3 python3-pip`

## Install

**macOS**
```sh
pip install wxPython
```

macOS でインストールに失敗する場合は wheel を指定してください:
```sh
pip install -U -f https://extras.wxpython.org/wxPython4/extras/macosx/cocoa wxPython
```

**Windows**
```sh
pip install wxPython
```

**Linux (Ubuntu/Debian)**
```sh
sudo apt install libwx-gtk3u-dev
pip install wxPython
```
Or download a pre-built wheel from https://extras.wxpython.org/wxPython4/extras/linux/

## Run

```sh
python main.py
```

> Windows: use `python` instead of `python3` if needed.

## Architecture

wxPython の wx.Frame ベース構成。データモデルとウィジェット部品をファイルで分離し、`main.py` がメインウィンドウを構築する。

```
.
├── main.py         # エントリーポイント・wx.App・メインウィンドウ構築
├── data.py         # Todo データモデル・TabFilter・状態管理
├── theme.py        # カラー・スタイル定数
└── widgets/        # タブ・入力欄・Todo 行の wxPython ウィジェット部品
```