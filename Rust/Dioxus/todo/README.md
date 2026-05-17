# Dioxus Todo

Rust Todo app using [Dioxus](https://dioxuslabs.com/) 0.5 — React-inspired declarative UI framework for desktop.

## Requirements

- Rust (stable) 1.70+

Install Rust on all platforms via https://rustup.rs/:
```sh
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

**Windows**: `winget install Rustlang.Rustup` or download rustup-init.exe from https://rustup.rs/

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

## Architecture

Dioxus の React インスパイア宣言的コンポーネント構成。状態は `use_signal` フックで管理し、コンポーネントをファイルで分離する。

```
src/
├── main.rs         # エントリーポイント・dioxus::launch・ルートコンポーネント
├── data.rs         # Todo データモデル・TabFilter・状態型定義
└── components/     # 入力欄・タブ・Todo リストの Dioxus コンポーネント
```