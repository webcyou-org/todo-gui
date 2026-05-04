# Step-by-Step Implementation Guide

新しいフレームワークでTodoアプリを実装する際の進め方とナレッジをまとめたドキュメント。

## 進め方の原則

- **1ステップ1コンパイル**: 各ステップ終了時に必ず `cargo build` / `npm run build` 等でビルドを通す
- **プレースホルダー方式**: 未実装部分は `"[Tabs]"` などのダミーテキストで場所を確保してから実装する
- **コンパイルエラーはその場で直す**: エラーを持ち越さない
- **ファイル分割は最後**: 動くものができてから構造を整理する

---

## 共通ステップ構成

| Step | 内容 |
|------|------|
| 1 | データモデル定義（Todo / TabFilter / AppState相当） |
| 2 | ウィンドウ設定 + 背景色・タイトル・レイアウト骨格 |
| 3 | Input フィールド（テキスト入力 + Enter でタスク追加） |
| 4 | Tab メニュー（All / Active / Completed 切り替え） |
| 5 | Todo リスト（フィルタ連動・チェックボックス・打ち消し線） |
| 6 | ファイル分割（data / components / widget など） |

---

## Rust / Druid (0.8.3)

### 各ステップの要点

**Step 1 — データモデル**
- `#[derive(Clone, Data, Lens, PartialEq)]` が必須
- リストは `druid::im::Vector<T>` を使う（標準 `Vec` は `Data` を実装しない）
- `Cargo.toml` に `druid = { version = "0.8.3", features = ["im"] }` と書く

**Step 2 — レイアウト骨格**
- `Flex::column().cross_axis_alignment(CrossAxisAlignment::Start)` で縦並び
- `Padding::new((24.0, 10.0), column).background(BG).expand()` で背景・パディングを一括設定
- デザイントークンは `const BG: Color = Color::rgb8(...)` でファイル先頭に定数化

**Step 3 — Input フィールド**
- `TextBox::new()` のスタイルは `env_scope` でテーマキーを上書きする
  ```rust
  .env_scope(|env, _: &AppState| {
      env.set(theme::BACKGROUND_LIGHT, INPUT_BG);
      env.set(theme::TEXTBOX_INSETS, Insets::new(16.0, 9.0, 16.0, 9.0)); // 垂直中央揃え
      env.set(theme::TEXTBOX_BORDER_RADIUS, 4.0_f64);
      // ...
  })
  ```
- Enter キーは `Controller` トレイトで横取りする（`ctx.set_handled()` でTextBoxに渡さない）

**Step 4 — Tab メニュー**
- `Either::new(条件, 太字ラベル, 通常ラベル)` でアクティブ時のみ Bold に切り替える
- タブクリックは `.on_click(move |_ctx, data: &mut AppState, _| { data.active_tab = ...; })`

**Step 5 — Todo リスト**
- `List::new(|| make_todo_row())` + カスタム `Lens` でフィルタ連動を実現
- カスタム `FilteredLens` の `with_mut` で変更を元データに書き戻す（最重要）
  ```rust
  fn with_mut<V, F: FnOnce(&mut Vector<Todo>) -> V>(&self, data: &mut AppState, f: F) -> V {
      let mut filtered = data.filtered_todos();
      let result = f(&mut filtered);
      for ft in &filtered {
          if let Some(t) = data.todos.iter_mut().find(|t| t.id == ft.id) {
              *t = ft.clone(); // 書き戻し
          }
      }
      result
  }
  ```
- 打ち消し線は `Widget<Todo>` を実装するカスタム `Strikethrough<W>` ラッパーで `paint()` に横線を追加
- チェックボックスは `Painter` + `BezPath` で円形＋チェックマークを手描き

**Step 6 — ファイル分割**
```
src/
├── main.rs          # build_ui() + main()
├── data.rs          # Todo / TabFilter / AppState
├── lens.rs          # FilteredLens
├── theme.rs         # デザイントークン定数
└── widget/
    ├── mod.rs
    ├── input.rs     # InputController + build_input()
    ├── tabs.rs      # tab_button() + build_tabs()
    └── todo_item.rs # Strikethrough + make_checkbox() + make_todo_row()
```

### Druid 固有の注意点

- `Label` に打ち消し線はない → カスタム `Widget<T>` 実装が必要
- `List` のアイテム間スペースは `Insets::new(0, 0, 0, 5)` を各アイテムに付ける
- フォーカス時ボーダーは `theme::PRIMARY_LIGHT` を上書き
- プレースホルダー色は `theme::PLACEHOLDER_COLOR` を上書き

---

## Rust / Dioxus (0.5.6)

### 各ステップの要点

**Step 1 — データモデル**
- `#[derive(Clone, PartialEq)]` のみでOK（`Data` トレイト不要）
- 状態は `use_signal(|| ...)` で管理

**Step 2 — ウィンドウ設定**
- `dioxus::LaunchBuilder` は存在しない（0.5.6時点）
- 正しい起動方法:
  ```rust
  use dioxus::desktop::{Config, WindowBuilder};
  use dioxus::desktop::tao::dpi::LogicalSize;
  // launch は pub mod なので :: が必要
  dioxus::desktop::launch::launch(App, vec![], config);
  ```
- グローバルCSSは `rsx!` 内の `style { "..." }` 要素で注入

**Step 3 — Input フィールド**
- `oninput: move |e| input.set(e.value())` でリアルタイム同期
- Enter キーは `onkeydown: move |e| { if e.key() == Key::Enter { ... } }`
- フォーカス時スタイルは `style {}` 内の `.class:focus` CSS擬似クラスで対応（Druidより遥かにシンプル）
- `add_todo` クロージャは `let mut add_todo = move || { ... }` と `mut` が必要

**Step 4 — Tab メニュー**
- `for tab in [TabFilter::All, ...]` でタブを列挙
- アクティブ判定: `class: if is_active { "tab-btn active" } else { "tab-btn" }`

**Step 5 — Todo リスト**
- フィルタリングは通常の変数計算で済む（Druidのカスタム Lens 不要）
  ```rust
  let filtered: Vec<Todo> = todos.read().iter()
      .filter(|t| active_tab.read().matches(t))
      .cloned()
      .collect();
  ```
- 打ち消し線は `text-decoration: line-through;` のCSSのみ
- カスタムチェックボックス: `appearance: none` + `::before` 疑似要素でチェックマーク
  - チェックマークの位置調整は `top` / `left` の px 値で微調整
- `Signal<T>` は `Copy` なので `onchange` クロージャに直接キャプチャできる
  ```rust
  onchange: move |_| {
      if let Some(t) = todos.write().iter_mut().find(|t| t.id == id) {
          t.is_completed = !t.is_completed;
      }
  }
  ```
- `toggle` クロージャも `let mut toggle = move |id| { ... }` と `mut` が必要

**Step 6 — ファイル分割**
```
src/
├── main.rs                  # App + グローバルCSS + main()
├── data.rs                  # Todo / TabFilter
└── components/
    ├── mod.rs
    ├── input.rs             # TodoInput コンポーネント
    ├── tabs.rs              # TabMenu コンポーネント
    └── todo_list.rs         # TodoList + TodoItem コンポーネント
```
- `Signal<T>` はコンポーネントのpropsに直接渡せる（`Copy` なので所有権問題なし）

### Dioxus 固有の注意点

- `Signal` を変更するクロージャは `let mut` が必要
- コンポーネントのpropsは `Signal<T>` をそのまま受け取れる
- CSSはWebViewで動くので擬似クラス・擬似要素が全て使える
- `key: "{id}"` を各リストアイテムに付けると差分更新が効率化される

---

## DruidとDioxusの実装量比較

| 機能 | Druid | Dioxus |
|------|-------|--------|
| 打ち消し線 | カスタム `Widget<T>` 実装（約30行） | CSS 1行 |
| フィルタリング | カスタム `Lens` 実装（約20行） | 変数計算（3行） |
| チェックボックス | `Painter` + `BezPath` 手描き（約20行） | CSS `::before` |
| フォーカスボーダー | `env_scope` でテーマ上書き | CSS `:focus` |
| コンポーネント間の状態共有 | `Lens` or `Command` | `Signal<T>` を直接渡す |