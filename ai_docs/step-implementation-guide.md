# Step-by-Step Implementation Guide

新しいフレームワークでTodoアプリを実装する際の進め方とナレッジをまとめたドキュメント。

> **デザイントークンの正典は [`design/tokens.md`](../design/tokens.md) を参照すること。**  
> 色・タイポグラフィ・スペーシング・コンポーネントサイズはすべてそちらに定義されている。  
> 実装前に必ず確認し、値を変更する場合はまず `tokens.md` を更新してから各実装へ反映する。

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

---

## Rust / Vizia (git HEAD 7dccf72)

Cargo.toml: `vizia = {git = "https://github.com/vizia/vizia"}`

### 各ステップの要点

**Step 1 — データモデル**
- `#[derive(Lens, Clone, PartialEq, Debug)]` が必要
- `TabFilter` は `usize`（0=All, 1=Active, 2=Completed）で管理するか enum で定義
- `AppData` に `filtered_todos: Vec<Todo>` を派生フィールドとして持ち、`todos`/`active_tab` 変更時に `recompute_filtered()` で同期
- イベントは `AppEvent` enum で定義し、`impl Model for AppData` の `event()` でハンドル

**Step 2 — ウィンドウ設定**
```rust
Application::new(|cx| {
    AppData::new().build(cx);
    // UI...
})
.title("ToDo")
.inner_size((800, 600))
.run()
```
- 背景色は CSS で設定（後述）

**Step 3 — Input フィールド**
- `Textbox::new(cx, AppData::input_text)` でレンズバインド
- `.placeholder("Add Task")` でプレースホルダー
- `.on_edit(|cx, text| cx.emit(AppEvent::SetInputText(text)))` で入力同期
- `.on_submit(|cx, _text, enter| { if enter { cx.emit(AppEvent::AddTodo); } })` で Enter のみ追加
  - `bool` が `true` = Enter キー、`false` = blur（フォーカス外れ）
- モデル側で `self.input_text = String::new()` するとテキストボックスが自動的にクリア
- スタイルはインライン CSS 文字列で上書き（詳細は後述）

**Step 4 — Tab メニュー**
- `HStack::new` の中で `Button::new` を3つ並べる
- アクティブタブの Bold は `AppData::active_tab` への `Binding` で切り替え、または `font_weight` を lens でバインド
- クリック: `Button::on_press(|cx| cx.emit(AppEvent::SetActiveTab(i)))`

**Step 5 — Todo リスト**
- `ScrollView::new(cx, 0.0, 0.0, false, true, |cx| { List::new(cx, AppData::filtered_todos, ...) })` で縦スクロール対応
- `List::new` のアイテムレンダリング:
  ```rust
  List::new(cx, AppData::filtered_todos, |cx, _idx, item| {
      Binding::new(cx, item, |cx, todo_lens| {
          let todo = todo_lens.get(cx).clone();
          let id = todo.id;
          let is_completed = todo.is_completed;
          HStack::new(cx, |cx| {
              // カスタム円形チェックボックス
              Element::new(cx)
                  .size(Pixels(16.0))
                  .corner_radius(Pixels(8.0))
                  .border_width(Pixels(2.0))
                  .border_color(if is_completed { C_ACCENT } else { C_CB_BORDER })
                  .background_color(if is_completed { C_ACCENT } else { Color::rgba(0,0,0,0) })
                  .on_press(move |cx| cx.emit(AppEvent::ToggleTodo(id)));
              // テキスト + 打ち消し線
              Label::new(cx, &todo.task)
                  .color(if is_completed { C_MUTED } else { C_TEXT })
                  .text_decoration_line(if is_completed {
                      TextDecorationLine::Strikethrough
                  } else {
                      TextDecorationLine::empty()
                  });
          });
      });
  });
  ```
- Vizia は `text-decoration-line: strikethrough` を CSS と Rust 両方でサポートしている

**Step 6 — ファイル分割**
```
src/
├── main.rs          # Application::new + build_ui + main()
├── data.rs          # Todo / AppData / AppEvent / Model impl
├── theme.rs         # Color 定数 + CSS 文字列定数
└── components/
    ├── mod.rs
    ├── input.rs     # build_input()
    ├── tabs.rs      # build_tabs()
    └── todo_list.rs # build_todo_list() + todo_item()
```

### CSS スタイリングの要点

Vizia はインライン CSS 文字列でテーマを上書きできる:
```rust
cx.add_stylesheet(STYLE).expect("Failed to add stylesheet");
```

主要な CSS プロパティ名（`border-radius` ではなく `corner-radius`）:
```css
/* ウィンドウ背景 */
* { background-color: #1C1C1C; }

/* TextBox カスタム */
textbox {
    background-color: #303030;
    border-color: transparent;
    border-width: 1px;
    corner-radius: 4px;
    color: #FFFFFF;
    height: 35px;
    padding-left: 16px;
    padding-right: 16px;
}
textbox:checked,
textbox:focus-visible {
    border-color: #5DC2AF;
}
textbox > label.placeholder {
    color: #9B9B9B;
}

/* Todo アイテム */
.todo-item {
    background-color: #2A2A2A;
    height: 35px;
    corner-radius: 4px;
    padding: 10px;
}
```

### Vizia 固有の注意点

- **`corner-radius`** が正しい CSS プロパティ名（`border-radius` は機能しない場合あり）
- **`textbox:checked`** = テキスト入力中（フォーカス+編集状態）の擬似クラス（Web の `:focus` 相当）
- **`Binding::new`** の中でウィジェットを作ると変化のたびにサブツリーが再構築される（正常動作）
- **`Data` トレイト**: `Binding::new(cx, lens, ...)` を使う場合、lens の Target 型が `Data` を実装している必要がある。カスタム構造体は以下で対応:
  ```rust
  impl Data for Todo {
      fn same(&self, other: &Self) -> bool { self == other }
  }
  ```
- `on_submit` の `bool` 引数: `true` = Enter、`false` = blur（Enter のみ追加したい場合は `if enter` で分岐）
- `List::new` の `item` 引数はレンズ — 直接 `.map()` や `Binding::new` に使える
- `Color::rgb(r, g, b)` は `const fn` なので定数に使える
- `FontWeight(700)` が Bold
- `TextDecorationLine::Strikethrough` で打ち消し線（`vizia::prelude::*` でインポート可能）
- `ScrollView::new(cx, 0.0, 0.0, false, true, content_fn)` で縦スクロール

---

## DruidとDioxusの実装量比較

| 機能 | Druid | Dioxus |
|------|-------|--------|
| 打ち消し線 | カスタム `Widget<T>` 実装（約30行） | CSS 1行 |
| フィルタリング | カスタム `Lens` 実装（約20行） | 変数計算（3行） |
| チェックボックス | `Painter` + `BezPath` 手描き（約20行） | CSS `::before` |
| フォーカスボーダー | `env_scope` でテーマ上書き | CSS `:focus` |
| コンポーネント間の状態共有 | `Lens` or `Command` | `Signal<T>` を直接渡す |