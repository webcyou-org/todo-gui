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

## Architecture

Druid のデータ駆動リアクティブ UI パターン。`AppState` を `Data` トレイトで定義し、Lens でフィールドを部分的に参照してウィジェットにバインドする。

```
src/
├── main.rs         # エントリーポイント・AppLauncher・ルートウィジェット構築
├── data.rs         # AppState・Todo・TabFilter（Druid Data/Lens 実装）
├── lens.rs         # カスタム Lens 定義
├── theme.rs        # カラー・スタイル定数
└── widget/         # 入力欄・タブ・Todo リストのカスタムウィジェット
```