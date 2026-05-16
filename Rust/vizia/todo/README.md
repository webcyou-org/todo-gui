# Vizia Todo

Rust Todo app using [Vizia](https://github.com/vizia/vizia) (git HEAD) — declarative GUI framework with CSS styling.

## Requirements

- Rust (stable) 1.70+

```sh
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

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