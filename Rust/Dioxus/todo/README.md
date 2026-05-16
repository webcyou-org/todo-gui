# Dioxus Todo

Rust Todo app using [Dioxus](https://dioxuslabs.com/) 0.5 — React-inspired declarative UI framework for desktop.

## Requirements

- Rust (stable) 1.70+

```sh
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

## Install（Dioxus CLI）

```sh
cargo install dioxus-cli
```

## Run

**デスクトップアプリとして起動（推奨）:**

```sh
cargo run
```

**ホットリロード付き開発モード:**

```sh
dx serve --hot-reload --platform desktop
```