# Xilem Todo

Rust/Xilem (0.4) で実装した Todo アプリ。

## Requirements

- Rust 1.82 以降（`use<>` 構文サポート）
- macOS / Linux / Windows（Xilem は wgpu ベースでクロスプラットフォーム対応）

## Build

```sh
cargo build
```

## Run

```sh
cargo run
```

## File Structure

```
src/
├── main.rs              # エントリーポイント・app_logic・ウィンドウ設定
├── data.rs              # データモデル（Todo / TabFilter / AppState）
├── theme.rs             # デザイントークン定数（Color 定数）
└── components/
    ├── mod.rs           # モジュール宣言
    ├── input.rs         # TodoInput コンポーネント
    ├── tabs.rs          # TabMenu コンポーネント
    └── todo_item.rs     # TodoItem 行 / TodoList コンポーネント
```

## Architecture

Xilem の reactive view tree をベースに MVC パターンを採用。`AppState` が Model、view 関数群が View、`on_enter`/`on_press` クロージャが Controller に相当する。

| レイヤー | ファイル | 役割 |
|---------|---------|------|
| Model | `data.rs` | 状態管理・ビジネスロジック（add_todo / toggle / filtered_todos） |
| View | `components/` | UI 描画（input / tabs / todo_item） |
| Controller | `main.rs` クロージャ | ユーザー入力 → Model への橋渡し |

## Notes

- **`Color::from_rgb8` は `const fn`** なので `const` 定数として定義できる。`theme.rs` に集約。
- **`text_color()` は `Self` 返し、`placeholder_color()` は `Prop<...>` 返し** — Style trait の chain 順序に注意。`Self`-returning メソッドをすべて先に呼んでから Style メソッドを続ける。
- **`FlexSpacer::Fixed(n.px())`** には `use xilem::masonry::properties::types::AsUnit as _;` が必要。
- **`Padding::from_vh(vertical, horizontal)`** で上下/左右を別指定できる（配列では渡せない）。
- **チェックボックスの円形表示** は `sized_box(button(...)).width(16.px()).height(16.px())` + `.corner_radius(8.)` で実現。
- **打ち消し線** は Xilem 0.4 の `label` 高レベル API では未サポート（`StyleProperty::Strikethrough` は Masonry 低レベル層のみ）。完了タスクはテキスト色を `C_MUTED` (#9B9B9B) に変更して代替表示。
- **スクロール** は `portal(flex_col(rows))` で対応。
- **`flex_col` のデフォルト `CrossAxisAlignment` は `Center`（横中央）**。左寄せにするには `.cross_axis_alignment(CrossAxisAlignment::Fill)` を指定する（`Stretch` は存在せず `Fill` が正しい）。