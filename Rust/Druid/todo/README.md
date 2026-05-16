# Druid Todo

Rust Todo app using [Druid](https://github.com/linebender/druid) 0.8.3 — data-driven reactive GUI framework.

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