# Implementation Tasks

新しいフレームワークでTodoアプリを実装する際のチェックリストと手順。

## Checklist per Implementation

### 1. プロジェクトセットアップ

- [ ] フレームワークのインストール・プロジェクト初期化
- [ ] ウィンドウサイズを `800 x 600 px` に設定
- [ ] ダークテーマ背景色 `#1C1C1C` を設定

### 2. データモデル実装

- [ ] `Todo` エンティティ (`id`, `task`, `isCompleted`) を定義
- [ ] `TabMenu` エンティティ (`text`, `isActive`) を定義
- [ ] `TodoModel` を実装
  - [ ] `getData()`
  - [ ] `addTodo(task)`
  - [ ] `findById(id)`
  - [ ] `changeCompleted(todo)`
  - [ ] `getFilteredTodos(tab)`
  - [ ] `removeData(id)`（任意）
- [ ] `MenuModel` を実装
  - [ ] `setActiveTab(tabItem)`
  - [ ] `getActiveTab()`
  - [ ] `getTabList()`
- [ ] サンプルデータを初期値として設定

### 3. UIコンポーネント実装

#### Title
- [ ] テキスト「ToDo」を表示
- [ ] 色: `#FFFFFF`, フォントサイズ: `18px`, ボールド
- [ ] マージンボトム: `14px`

#### TodoInput
- [ ] テキスト入力フィールドを配置
- [ ] プレースホルダー: `Add Task` (色: `#9B9B9B`)
- [ ] テキスト色: `#FFFFFF`
- [ ] 背景色: `#303030`
- [ ] 最小幅: `430px`, 高さ: `35px`
- [ ] 角丸: `4px`
- [ ] パディング: 上下 `4px`, 左右 `16px`
- [ ] マージンボトム: `14px`
- [ ] フォーカス時ボーダー: `1px solid #5DC2AF`
- [ ] Enter/Submit で `addTodo()` を呼び出し、入力欄をクリア

#### TabMenu
- [ ] `All` / `Active` / `Completed` の3タブを横並びで配置
- [ ] テキスト色: `#D2D2D2`, フォントサイズ: `14px`, 行高: `28px`
- [ ] 左右パディング: `8px`
- [ ] アクティブタブはボールド表示
- [ ] タブクリックで `setActiveTab()` → TodoList再描画

#### TodoList
- [ ] スクロール可能なリスト領域を配置
- [ ] 各アイテム最小幅: `430px`, 高さ: `35px`
- [ ] 背景色: `#2A2A2A`, パディング: `10px`, 角丸: `4px`
- [ ] マージンボトム: `5px`

#### TodoItem (各行)
- [ ] チェックボックスを左端に配置
  - [ ] 幅・高さ: `16px`, 角丸: `8px`（円形）
  - [ ] ボーダー: `2px solid #D9D9D9`
  - [ ] チェック済み: ボーダー色 `#5DC2AF` のチェックマーク表示
  - [ ] マージン右: `18px`
- [ ] タスクテキストを表示
  - [ ] フォントサイズ: `14px`, 色: `#D2D2D2`
  - [ ] 完了時: 打ち消し線 (strikethrough)
- [ ] チェックボックスクリックで `changeCompleted()` を呼び出し

### 4. フィルタリング連動

- [ ] タブ切替時に `getFilteredTodos(activeTab)` でリストを更新
- [ ] チェックボックストグル後に現在タブでリストを再フィルタ

### 5. MV\*\* アーキテクチャ整理

- [ ] Model（TodoModel, MenuModel）をViewから分離
- [ ] フレームワークに応じて Controller / ViewModel を実装
- [ ] View はデータ表示のみ担当し、ロジックをModelに委譲

### 6. 動作確認

- [ ] タスク追加（空文字は無視）
- [ ] 完了トグル（チェック ↔ 未チェック / 打ち消し線切替）
- [ ] All / Active / Completed タブ切替とフィルタリング
- [ ] ウィンドウサイズ 800x600 で起動
- [ ] デザイントークンが `design/todo@1.png` と一致

## Design Tokens Reference

| トークン | 値 |
|----------|----|
| 背景色 | `#1C1C1C` |
| 入力フィールド背景 | `#303030` |
| Todoアイテム背景 | `#2A2A2A` |
| タイトル文字色 | `#FFFFFF` |
| 一般テキスト色 | `#D2D2D2` |
| プレースホルダー色 | `#9B9B9B` |
| アクセントカラー | `#5DC2AF` |
| チェックボックスボーダー | `#D9D9D9` |
| コンテンツパディング | 上下 `10px`, 左右 `24px` |

## Recommended File Structure

```
<Language>/<Framework>/
├── src/
│   ├── model/
│   │   ├── todo_model.*     # TodoModel + Todo
│   │   └── menu_model.*     # MenuModel + TabMenu
│   ├── view/                # UIコンポーネント（フレームワーク依存）
│   ├── controller/          # Controller / ViewModel（必要な場合）
│   └── const/               # 定数・初期データ
├── main.*                   # エントリーポイント
└── README.md                # セットアップ手順
```

## Implementation Priority (Remaining)

未実装フレームワークの推奨着手順序:

1. **Qt for Go** (`Go/QtforGo/`) - ディレクトリ作成済み
2. **Rust/Xilem** - Druidの後継、モダンなRust UI
3. **C#/WinForms** - シンプルで学習コスト低
4. **Rust/Leptos** - WebAssembly対応
5. **C#/UWP** / **C#/Xamarin.Forms** - Windowsエコシステム補完