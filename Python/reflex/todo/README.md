# Reflex Todo

Python Todo app using [Reflex](https://reflex.dev/) — full-stack web framework in pure Python.

## Requirements

- Python 3.9+
- Node.js 18+ (Reflex のフロントエンドビルドに使用)

Python and Node.js are available on all platforms:
- macOS: `brew install python3 node`
- Windows: `winget install Python.Python.3 OpenJS.NodeJS`
- Linux: `sudo apt install python3 python3-pip nodejs npm`

## Install

```sh
pip install reflex
```

## Initialize (初回のみ)

```sh
reflex init
```

## Run

```sh
reflex run
```

ブラウザで `http://localhost:3000` が自動的に開きます。

## Architecture

Reflex のフルスタック Python 構成。状態管理・イベントハンドラーをサーバーサイドの Python クラスで定義し、フロントエンドは Reflex が自動的に React にコンパイルする。

```
todo/
├── todo.py         # ルートページ・UI 定義・State クラス（状態管理・CRUD）
├── rxconfig.py     # Reflex アプリ設定
└── assets/         # 静的アセット
```