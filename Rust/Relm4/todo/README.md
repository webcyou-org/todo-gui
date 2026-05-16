# ToDo - Relm4

Rust + [Relm4](https://relm4.org/) (GTK4) で実装した ToDo アプリケーション。

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

Relm4 の Elm インスパイア MVC パターン（Model / Update / View）。GTK4 ウィジェットを Relm4 マクロで宣言的に記述し、コンポーネントをファイルで分離する。

```
src/
├── main.rs         # エントリーポイント・RelmApp 起動・ルートコンポーネント定義
├── data.rs         # AppState・Todo・TabFilter・Message 型定義
├── theme.rs        # カラー・CSS 定数
└── components/     # 入力欄・タブ・Todo リストの Relm4 コンポーネント
```
