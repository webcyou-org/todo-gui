# Vizia Todo

Rust Todo app using [Vizia](https://github.com/vizia/vizia) (git HEAD) — declarative GUI framework with CSS styling.

## Requirements

- Rust (stable) 1.70+

Install Rust on all platforms via https://rustup.rs/:
```sh
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

**Windows**: `winget install Rustlang.Rustup` or download rustup-init.exe from https://rustup.rs/

> Vizia は git リポジトリから直接取得されます（`Cargo.toml` 参照）。

## Build & Run

```sh
cargo run
```

本番ビルド:

```sh
cargo build --release
./target/release/todo
```

## Architecture

Vizia の宣言的・リアクティブ UI パターン。`Model` トレイトで状態を定義し、CSS スタイリングとビューコンポーネントを組み合わせる。

```
src/
├── main.rs         # エントリーポイント・Application 起動・ルートビュー構築
├── data.rs         # AppState・Todo・TabFilter・Model・Event 定義
├── theme.rs        # カラー定数
└── components/     # 入力欄・タブ・Todo リストの Vizia ビュー部品
```