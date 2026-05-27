# Makepad Todo

Rust Todo app using [Makepad](https://github.com/makepad/makepad) 1.0 — GPU-accelerated live-design UI framework.

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

本番ビルド:

```sh
cargo build --release
./target/release/todo
```

> ホットリロードを有効にするには nightly が必要:
> ```sh
> MAKEPAD=lines cargo +nightly run
> ```

## Architecture

Makepad の `live_design!` DSL で UI レイアウト・スタイルを宣言し、Rust の `MatchEvent` / `Widget` トレイトでロジックを実装する 2 層構成。カスタムウィジェットは `#[derive(Live, LiveHook, Widget)]` で定義する。

```
src/
├── main.rs                 # エントリーポイント・App ウィジェット・live_design・イベント処理
├── data.rs                 # Todo・TabFilter・AppData データモデル
└── components/
    ├── mod.rs
    └── todo_list.rs        # TodoList カスタムウィジェット（PortalList ベース）
```