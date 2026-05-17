# Kivy Todo

Python Todo app using [Kivy](https://kivy.org/) — cross-platform GUI framework.

## Requirements

- Python 3.9+

Python is available on all platforms. Install from https://python.org or:
- macOS: `brew install python3`
- Windows: `winget install Python.Python.3`
- Linux: usually pre-installed; `sudo apt install python3 python3-pip`

## Install

Works on all platforms:
```sh
pip install kivy
```

macOS で OpenGL 警告が出る場合:

```sh
pip install kivy[base]
```

## Run

```sh
python main.py
```

> Windows: use `python` instead of `python3` if needed.

## Architecture

Kivy のウィジェットツリーによる宣言的 UI 構成。データモデルとコンポーネントをファイルで分離し、`main.py` がアプリを起動する。

```
.
├── main.py         # エントリーポイント・App クラス・ルートウィジェット構築
├── data.py         # Todo データモデル・TabFilter・状態管理
├── theme.py        # カラー・フォント定数
└── components/     # 入力欄・タブ・リストの Kivy ウィジェット部品
```