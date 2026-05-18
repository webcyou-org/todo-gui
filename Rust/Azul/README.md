# Azul Todo

Rust Todo app using [Azul](https://azul.rs/) — a functional, reactive GUI framework built on Mozilla WebRender.

> **注意: macOS ARM64 (Apple Silicon) でのビルドには追加手順が必要です。**
> 詳細は [Notes](#notes) を参照してください。

## Requirements

- Rust (stable) 1.70+

## Build & Run

```sh
cargo run
```

本番ビルド:

```sh
cargo build --release
```

## File Structure

```
src/
├── main.rs              # エントリーポイント + layout() + ウィンドウ設定
├── data.rs              # データモデル (Todo, TabFilter, AppState, ToggleData)
├── theme.rs             # デザイントークン定数
└── components/
    ├── mod.rs
    ├── input.rs         # Input コンポーネント + Enter キー追加ロジック
    ├── tabs.rs          # Tab メニュー (All / Active / Completed)
    └── todo_list.rs     # TodoItem + TodoList + チェックボックストグル
```

## Architecture

MVC パターンを採用。Azul の `extern "C"` コールバック + `RefAny` 型消去により状態を管理する。

| レイヤー | ファイル | 役割 |
|---------|---------|------|
| Model | `src/data.rs` | 状態管理・ビジネスロジック |
| View | `src/main.rs`, `src/components/` | DOM 構築・`layout()` 関数 |
| Controller | `extern "C"` コールバック関数 | イベント → AppState 更新 |

## Notes

### macOS ARM64 でのビルド方法

Azul 1.0.0-alpha4 は pre-built バイナリへの動的リンクを前提としていますが、
macOS ARM64 向けバイナリが公式リリースに含まれていないため、
本実装は **git ソース + `link-static` フィーチャー** でビルドします。

`link-static` ビルドには **生成コード** (`dll_api_static.rs`) が必要です。
初回ビルド前に以下の手順で生成してください:

```sh
# 1. azul リポジトリをクローン
git clone https://github.com/fschutt/azul /tmp/azul-src

# 2. コードジェネレータを実行
cd /tmp/azul-src/doc && cargo run --release -- codegen all

# 3. 生成ファイルを cargo git キャッシュにコピー
AZUL_CHECKOUT=$(ls -d ~/.cargo/git/checkouts/azul-*/e57d9e9*/ 2>/dev/null | head -1)
mkdir -p "$AZUL_CHECKOUT/target/codegen/v2"
cp /tmp/azul-src/target/codegen/v2/dll_api_static.rs  "$AZUL_CHECKOUT/target/codegen/v2/"
cp /tmp/azul-src/target/codegen/v2/dll_api_build.rs   "$AZUL_CHECKOUT/target/codegen/v2/"
cp /tmp/azul-src/target/codegen/v2/dll_api_dynamic.rs "$AZUL_CHECKOUT/target/codegen/v2/"
cp /tmp/azul-src/target/codegen/v2/reexports.rs       "$AZUL_CHECKOUT/target/codegen/v2/"

# 4. 通常通りビルド
cargo run
```

### Azul 固有の注意点

- `azul 0.1.0` (crates.io) は名前予約の空パッケージ — 使用不可
- `link-static` は WebRender 等 263 パッケージをまとめてビルドするため初回ビルドに数分かかる
- `extern "C"` コールバック必須: Azul の状態はすべて `RefAny` で型消去されて渡される
- 複数アイテムに個別の状態を渡すには `ToggleData { app: RefAny, id: usize }` のようなラッパーを `RefAny` でネストする
- `AzString::from("literal")` で `Into<AzString>` の型推論を明示的に解決する必要がある場合がある
- `with_inline_style(&format!(...))` は型エラーになる → `.as_str()` か変数経由で渡す
- `TextInputState`, `OnTextInputReturn`, `TextInputValid`, `CheckBoxState` は `azul::widgets` から import
- `VirtualKeyCode` は `azul::dom` から import