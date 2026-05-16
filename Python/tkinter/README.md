# tkinter Todo

Python Todo app using [tkinter](https://docs.python.org/3/library/tkinter.html) — Python の標準 GUI ライブラリ。

## Requirements

- Python 3.9+
- Tcl/Tk（Python に同梱）

## Run

```bash
python3 main.py
```

### macOS で tkinter が動かない場合

pyenv の Python は tcl-tk との依存関係で tkinter が動作しないことがある。  
Homebrew で Python と tkinter を別途インストールして実行する。

```bash
brew install python-tk@3.9
python3.9 main.py
```

## ファイル構成

```
tkinter/
├── main.py               # エントリーポイント・ルートウィンドウ
├── data.py               # データモデル（Todo, TodoModel, MenuModel）
├── theme.py              # カラー定数・フォント・描画ユーティリティ
└── components/
    ├── todo_input.py     # 入力フィールド
    ├── tabs.py           # タブメニュー（All / Active / Completed）
    └── todo_list.py      # Todo リスト（スクロール対応）
```