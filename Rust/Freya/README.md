# Freya Todo

Rust Todo app using [Freya](https://freyaui.dev/) 0.3.4 — cross-platform native GUI library powered by Skia and Dioxus.

## Requirements

- Rust (stable) 1.70+
- macOS, Windows, or Linux

```sh
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

## Run

```sh
cargo run
```

## File Structure

```
src/
├── main.rs              # エントリーポイント + ルートコンポーネント
├── data.rs              # データモデル (Todo, TabFilter)
├── theme.rs             # デザイントークン定数
└── components/
    ├── mod.rs
    ├── input.rs         # TodoInput コンポーネント
    ├── tabs.rs          # TabMenu コンポーネント
    └── todo_list.rs     # TodoList + TodoItem コンポーネント
```

## Architecture

MVC パターンを採用。Freya の RSX マクロと `use_signal` で状態をリアクティブ管理。

| レイヤー | ファイル | 役割 |
|---------|---------|------|
| Model | `data.rs` | 状態管理・ビジネスロジック |
| View | `components/` | UI 描画・イベント受付 |
| Controller | `main.rs` | 入力 → Signal への橋渡し |

## Notes

- Enter キーは `onglobalkeydown` イベントでルート `rect` が捕捉する
- Input スタイルは `InputThemeWith` で背景色・ボーダー・フォーカス色を上書き
- チェックボックスは `corner_radius: "8"` の `rect` で円形に描画
- テキスト打ち消し線は `label` の `decoration: "line-through"` 属性
- ボーダー形式: `"<width> inner/outer/center <color>"` (CSS の `solid` キーワードなし)
- サイズ単位 `fill` が利用可能な残りスペースを埋める (`fill-available` は無効)