# U++ Todo

C++ Todo app using [U++ (Ultimate++)](https://www.ultimatepp.org/).

## Requirements

- U++ フレームワーク（umk ビルドツール + uppsrc）
- macOS / Linux / Windows (via MSYS2)

> Windows: MSYS2 環境 (https://www.msys2.org/) を使用してください。

## Install

[U++ 公式サイト](https://www.ultimatepp.org/www$uppweb$download$en-us.html) からソースを取得し、`/tmp/ultimatepp/` 以下に展開してください。

```sh
# ソース取得（例）
git clone https://github.com/ultimatepp/ultimatepp /tmp/ultimatepp
cd /tmp/ultimatepp
# umk のビルド
cd uppsrc/umk && make
```

詳細は [U++ on Linux/macOS ガイド](https://www.ultimatepp.org/app$ide$install$en-us.html) を参照してください。

環境変数の確認（Makefile 参照）:

```sh
# デフォルト値
UMK   = /tmp/ultimatepp/umk
UPPSRC = /tmp/ultimatepp/uppsrc
```

## Build & Run

```sh
make build
make run
```

## Architecture

U++ の IDE レイアウト記述（`.upp`）を使ったシングルパッケージ構成。データモデルとウィジェット部品をファイルで分離する。

```
TodoApp/
├── main.cpp        # エントリーポイント・TopWindow 構築・イベント処理
├── data.h/cpp      # Todo データモデル・AppState・TabFilter
├── theme.h         # カラー・スタイル定数
├── TodoApp.upp     # U++ パッケージ定義
└── widgets/        # 入力欄・タブ・リストの U++ ウィジェット部品
```