# ToDo - gtk-rs

Rust + [gtk-rs](https://gtk-rs.org/) (GTK4) で実装した ToDo アプリケーション。

## Requirements

- Rust (stable)
- GTK4 development libraries

### Ubuntu / Debian

```bash
sudo apt-get install libgtk-4-dev
```

### macOS

```bash
brew install gtk4
```

## Build & Run

```bash
cargo run
```

## Architecture

gtk-rs の GTK4 Rust バインディングを使ったシングルパッケージ構成。データモデルとテーマをファイルで分離し、`main.rs` が GTK4 アプリケーションを構築する。

```
src/
├── main.rs         # エントリーポイント・gtk::Application・ウィンドウ構築
├── data.rs         # Todo データモデル・TabFilter・AppState
└── theme.rs        # カラー・CSS 定数
```
