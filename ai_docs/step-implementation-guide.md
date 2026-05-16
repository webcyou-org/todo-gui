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
| 7 | README.md ドキュメント作成（セットアップ・ビルド・起動手順） |
| 8 | git push 前のクリーンアップ（不要ファイル確認・.gitignore 整備） |

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

---

## Zig / GTK4

### 前提

- Zig 0.16.0 時点では `@cImport({ @cInclude("gtk/gtk.h"); })` が `translate-c` のクラッシュ（SIGBUS）で動作しない
- 代替手法: **手動 `extern fn` 宣言** を使う（`bindings.zig` に全宣言を集める）

### 各ステップの要点

**ビルド設定**
```zig
mod.linkSystemLibrary("gtk4", .{ .use_pkg_config = .force });
```
`pkg-config` で include / lib パスを自動取得する。

**コールバック**
- `callconv(.C)` は Zig 0.16.0 で廃止（`CallingConvention` が tagged union に変わった）
- 代替: `export fn cb_name(...)` でC互換の呼び出し規約を得る
- シグナル登録時: `@ptrCast(@constCast(&cb_name))` で `gpointer` にキャスト

**デザイントークン**
```zig
cairo_set_source_rgb(cr, @as(f64, 0x5D)/255.0, @as(f64, 0xC2)/255.0, @as(f64, 0xAF)/255.0);
```
hex リテラルはそのまま float 除算できないので `@as(f64, ...)` で明示キャストする。

**打ち消し線**
- CSS `.todo-text.completed { text-decoration-line: line-through; }` を `gtk_css_provider_load_from_string` で適用
- ウィジェットに `gtk_widget_add_css_class(lbl, "completed")` を呼ぶだけで反映される

**タブ切り替え**
- タブインデックスを `@ptrFromInt(i)` で `gpointer` に埋め込み、コールバックで `@intFromPtr(ud)` 取り出す

**ファイル構成**
```
src/
├── main.zig              # エントリー + export fn callbacks + onActivate
├── bindings.zig          # GTK4/Cairo extern fn 宣言 + 定数
├── data.zig              # データモデル（純粋Zig、GTK依存なし）
├── ctx.zig               # グローバル状態 var G: Ctx
└── components/
    ├── input.zig         # buildInput(cb) → gpointer
    ├── tabs.zig          # buildTabs(cb) → gpointer
    └── todo_list.zig     # export fn drawCb/pressedCb, rebuild(), appendItem()
```

### Zig/GTK4 固有の注意点

- `translate-c` は GTK4 ヘッダで SIGBUS クラッシュする → `extern fn` 手動宣言が唯一の実用解
- `callconv(.C)` が使えないため `export fn` を利用する（グローバルシンボルが増えるが問題なし）
- `@ptrCast` で `const` を落とすときは `@ptrCast(@constCast(ptr))` が必要（Zig 0.16 strict）
- GTK4 `gtk_css_provider_load_from_string` は GTK 4.12+ のみ存在（`load_from_data` は旧API）
- `gpointer = ?*anyopaque` で全 GObject ポインタを統一すると型エラーが減る

---

---

## Step 7 — README.md ドキュメント作成

### 配置場所

- `ToDo/` または `todo/` サブディレクトリがある場合 → その直下
- ない場合 → フレームワーク名のディレクトリ直下（例: `C++/bgfx-ImGui/README.md`）

### 構成

```markdown
# <Framework> Todo

一行説明。

## Requirements

- OS制約（Windows専用など）
- ランタイムバージョン（Python 3.9+、.NET 8.0+ など）
- 外部ツール（homebrew パッケージ、SDK workload など）

## Install

（依存パッケージの取得コマンド）

## Build

（ビルドが必要な場合のみ記載）

## Run

（起動コマンド）

## File Structure

（ファイル構成ツリー + 各ファイルの一行説明）

## Architecture

（採用パターンと役割分担テーブル）

## Notes

（フレームワーク固有の落とし穴・注意点）
```

### File Structure セクションの書き方

`src/` ディレクトリのツリーを示し、各ファイルの役割を `#` コメントで補足する。

````markdown
## File Structure

```
src/
├── main.*           # エントリーポイント
├── data.*           # データモデル
└── components/
    ├── input.*      # Input コンポーネント
    ├── tabs.*       # Tab メニュー
    └── todo_item.*  # Todo アイテム / リスト
```
````

### Architecture セクションの書き方

採用した MV** パターンを一文で示し、レイヤーとファイルの対応を表にまとめる。

```markdown
## Architecture

MVC パターンを採用。〈フレームワーク固有の一言説明〉。

| レイヤー | ファイル | 役割 |
|---------|---------|------|
| Model | `data.*` | 状態管理・ビジネスロジック |
| View | `...` | UI 描画・イベント受付 |
| Controller / ViewModel | `main.*` | 入力 → Model への橋渡し |
```

### Notes セクションの書き方

そのフレームワークを初めて触った開発者が詰まりやすい点を箇条書きで記載する。  
`step-implementation-guide.md` の実装ナレッジから厳選して転記する。

```markdown
## Notes

- 〈フレームワーク固有の注意点 1〉
- 〈フレームワーク固有の注意点 2〉
```

### 種別ごとの典型コマンド

| 種別 | Install | Build | Run |
|------|---------|-------|-----|
| Rust | — | `cargo build` | `cargo run` |
| Go | `go mod download` | — | `go run .` |
| C++ / CMake | — | `cmake -B build && cmake --build build` | `./build/<name>` |
| C++ / Makefile | — | `make` | `./<target>` |
| C# (.NET) | `dotnet restore` | — | `dotnet run` |
| Python | `pip install <pkg>` | — | `python main.py` |
| Node.js | `npm install` | （必要に応じて） | `npm start` / `npm run dev` |
| Flutter | — | — | `flutter run` |

### 注意事項

- Windows 専用フレームワーク（WPF・WinForms・UWP）は冒頭に `> Windows 専用` と明記する
- ビルドに数分かかる場合（bgfx、wxWidgets の初回ビルド等）はその旨を記載する
- homebrew パッケージ名は formula 名そのままを使う（`brew install <name>`）

### ルート README.md のリンク追加

実装完了後、リポジトリルートの `README.md` に対象フレームワークのリンクが未追加の場合は追加する。

```markdown
- [Compose Multiplatform](https://github.com/webcyou-org/todo-gui/tree/main/Kotlin/ComposeMultiplatform)
```

- リンク先は `https://github.com/webcyou-org/todo-gui/tree/main/<言語>/<フレームワーク名>` の形式
- 既にプレーンテキストで列挙されている場合はリンク付きに置き換える
- 言語セクション内の順序はそのまま維持する

---

## Step 8 — git push 前のクリーンアップ

### チェックリスト

```sh
# 1. 未追跡ファイル・変更一覧を確認
git status

# 2. 最終差分を確認
git diff HEAD
```

**ビルド生成物が .gitignore に含まれているか確認する:**

| 環境 | 除外すべきディレクトリ・ファイル |
|------|-------------------------------|
| Rust | `target/` |
| C++ / CMake | `build/`（空ディレクトリは `.gitkeep` で管理） |
| C# | `bin/`、`obj/` |
| Node.js | `node_modules/` |
| Python | `__pycache__/`、`*.pyc`、`.venv/`、`venv/` |
| Flutter | `build/`、`.dart_tool/` |
| 全般 | `.DS_Store`、`.idea/`、`*.o`、`*.out` |

**追加してはいけないもの:**
- APIキー・シークレット（`.env`、`*.pem` 等）
- コンパイル済みバイナリ（`.exe`、`.app` バンドル等）
- OS 固有の一時ファイル（`.DS_Store`、`Thumbs.db`）

### .gitignore の整備例

ルートの `.gitignore` に以下を追加・確認する:

```
# Rust
**/target/

# C++ build
**/build/

# .NET
**/bin/
**/obj/

# Node.js
**/node_modules/

# Python
**/__pycache__/
**/*.pyc
**/.venv/
**/venv/

# Flutter
**/.dart_tool/

# OS
.DS_Store
Thumbs.db

# IDE
.idea/
*.user
```

### push 前の最終確認

```sh
# 追跡されているファイルの一覧
git ls-files | sort

# 大きなファイルがないか確認（1MB超を検出）
git ls-files | xargs ls -la 2>/dev/null | awk '$5 > 1000000 {print $5, $9}'

# push
git push origin main
```

---

## DruidとDioxusの実装量比較

| 機能 | Druid | Dioxus |
|------|-------|--------|
| 打ち消し線 | カスタム `Widget<T>` 実装（約30行） | CSS 1行 |
| フィルタリング | カスタム `Lens` 実装（約20行） | 変数計算（3行） |
| チェックボックス | `Painter` + `BezPath` 手描き（約20行） | CSS `::before` |
| フォーカスボーダー | `env_scope` でテーマ上書き | CSS `:focus` |
| コンポーネント間の状態共有 | `Lens` or `Command` | `Signal<T>` を直接渡す |