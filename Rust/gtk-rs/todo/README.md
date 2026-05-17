# ToDo - gtk-rs

Rust + [gtk-rs](https://gtk-rs.org/) (GTK4) で実装した ToDo アプリケーション。

## Requirements

- Rust (stable)
- GTK4 development libraries

Install Rust via https://rustup.rs/ or `winget install Rustlang.Rustup` on Windows.

### macOS

```bash
brew install gtk4
```

### Windows

Install GTK4 via MSYS2: `pacman -S mingw-w64-x86_64-gtk4`

### Ubuntu / Debian

```bash
sudo apt-get install libgtk-4-dev
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
