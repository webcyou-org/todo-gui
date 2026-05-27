# Slint Todo

Rust Todo app using [Slint](https://slint.rs/) 1.7 — declarative UI framework with `.slint` markup.

## Requirements

- Rust (stable) 1.70+

Install Rust on all platforms via https://rustup.rs/:
```sh
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

**Windows**: `winget install Rustlang.Rustup` or download rustup-init.exe from https://rustup.rs/

## Build & Run

```sh
cargo run
```

> UI は `ui/` 以下の `.slint` ファイルで定義されています。  
> VS Code の [Slint 拡張機能](https://marketplace.visualstudio.com/items?itemName=Slint.slint) を入れるとプレビューが使えます。

## Architecture

Slint の宣言的マークアップと Rust ロジックの 2 層構成。`.slint` ファイルで UI を定義し、`build.rs` でコード生成した型を通じて Rust から状態をバインドする。

```
ui/                     # Slint マークアップ（UI 定義）
├── appwindow.slint     # メインウィンドウ・レイアウト
├── types.slint         # 共有型定義
└── components/         # 入力欄・タブ・Todo 行の Slint コンポーネント
src/                    # Rust ロジック
├── main.rs             # エントリーポイント・Slint ウィンドウ起動・コールバック登録
├── app.rs              # アプリケーションロジック・状態管理
└── data.rs             # Todo データモデル・TabFilter
```
