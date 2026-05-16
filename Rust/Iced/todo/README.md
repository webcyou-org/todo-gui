# Iced Todo

Rust Todo app using [Iced](https://iced.rs/) 0.12 — cross-platform GUI library inspired by Elm.

## Requirements

- Rust (stable) 1.70+

```sh
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

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

Iced の Elm アーキテクチャ（State / Message / Update / View）パターン。状態・スタイル・ビューをファイルで分離し、イミュータブルな状態更新でリアクティブ UI を実現する。

```
src/
├── main.rs         # エントリーポイント・iced::run・Application 実装
├── state.rs        # AppState・Todo・TabFilter・Message・update ロジック
├── view.rs         # view 関数・Element ツリー構築
└── style.rs        # カスタムスタイル・カラー定数
```