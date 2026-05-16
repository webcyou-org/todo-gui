# egui Todo

Rust Todo app using [egui](https://github.com/emilk/egui) / [eframe](https://github.com/emilk/egui/tree/master/crates/eframe) — immediate mode GUI library.

## Requirements

- Rust (stable) 1.70+

```sh
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
rustup update
```

**Linux** の場合は追加で:

```sh
sudo apt-get install libxcb-render0-dev libxcb-shape0-dev libxcb-xfixes0-dev libxkbcommon-dev libssl-dev
```

## Build & Run

```sh
cargo run --release
```

## Architecture

egui の即時モード GUI パターン。毎フレーム `update` 関数を呼び出して UI を宣言的に描画し、状態は `App` 構造体で一元管理する。

```
src/
├── main.rs         # エントリーポイント・eframe::run_native・App 起動
├── lib.rs          # App 構造体・eframe::App 実装（update 関数）
├── data.rs         # Todo データモデル・TabFilter・状態管理
├── app.rs          # UI 描画ロジック（egui ウィジェット呼び出し）
└── theme.rs        # カラー・スタイル定数
```