# Leptos Todo

Rust + [Leptos](https://leptos.dev/) (v0.6) による Todo アプリ。WebAssembly (CSR) でブラウザ上で動作する。

## Requirements

- Rust (stable)
- `wasm32-unknown-unknown` target
- `trunk` ビルドツール

```sh
rustup target add wasm32-unknown-unknown
cargo install trunk
```

## Run

```sh
trunk serve
```

ブラウザで `http://localhost:8080` を開く。

## Build

```sh
trunk build --release
```

`dist/` に最適化済み WASM + HTML が生成される。

## File Structure

```
src/
├── lib.rs               # App コンポーネント + CSS + エントリーポイント
├── data.rs              # データモデル (Todo / TabFilter)
└── components/
    ├── mod.rs
    ├── input.rs         # TodoInput コンポーネント
    ├── tabs.rs          # TabMenu コンポーネント
    └── todo_list.rs     # TodoList コンポーネント
```

## Architecture

MVVM パターンを採用。Leptos のリアクティブシグナルが ViewModel の役割を担う。

| レイヤー | ファイル | 役割 |
|---------|---------|------|
| Model | `data.rs` | データ構造・ビジネスロジック |
| ViewModel | `lib.rs` (App) | `RwSignal` による状態管理 |
| View | `components/` | UI 描画・イベント受付 |

## Notes

- Leptos CSR は `[lib] crate-type = ["cdylib", "rlib"]` と `src/lib.rs` が必要
- 状態シグナル (`RwSignal<T>`) は `Copy` なのでコンポーネント props に直接渡せる
- `create_memo` でフィルタ済みリストを派生させ、`For` コンポーネントで効率的に差分更新
- フォーカス時ボーダーは CSS `:focus` 擬似クラスで対応（Druid より遥かにシンプル）
- 打ち消し線は `text-decoration: line-through` の CSS 1 行で実現