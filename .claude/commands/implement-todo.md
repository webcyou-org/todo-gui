# implement-todo

指定したフレームワークで Todo アプリを仕様・デザインに沿って Step by Step で実装する。

## 事前確認

まず以下を読んで仕様・デザイン・進め方を把握すること:
- `ai_docs/requirement.md` — 機能要件・デザイン仕様
- `ai_docs/architecture.md` — クラス構成・データフロー
- `ai_docs/data-struture.md` — データモデル詳細
- `ai_docs/step-implementation-guide.md` — 過去実装の知見・注意点
- `design/tokens.md` — **デザイントークン正典（色・スペーシング・サイズはここが唯一の正）**
- `design/todo@1.png` — UIデザイン参照画像

引数でフレームワーク名が渡された場合（例: `/implement-todo Slint`）はそのフレームワークを対象とする。
渡されない場合はユーザーに確認する。

## 実装ステップ

以下の順で **1ステップずつ** 実装し、各ステップ終了時に必ずビルドを通してからユーザーに報告して次に進む。

### Step 1: データモデル
- `Todo` (id, task, is_completed) を定義
- `TabFilter` (All / Active / Completed) を定義
- アプリ全体の状態 (`AppState` 相当) を定義
- サンプルデータを初期値として設定
- **ビルド確認**

### Step 2: ウィンドウ設定 + レイアウト骨格
- ウィンドウサイズを **800 × 600 px** に設定
- 背景色 `#1C1C1C` を設定
- タイトル「ToDo」を `#FFFFFF / 18px / Bold` で配置
- Input・Tabs・List の場所をプレースホルダーで確保
- **ビルド確認**

### Step 3: Input フィールド
- プレースホルダーテキスト `Add Task`（色 `#9B9B9B`）
- 背景 `#303030`、テキスト色 `#FFFFFF`、高さ `35px`、角丸 `4px`
- フォーカス時ボーダー `1px solid #5DC2AF`
- Enter キーでタスク追加・入力欄クリア（空文字は無視）
- **ビルド確認**

### Step 4: Tab メニュー
- All / Active / Completed の3タブを横並びで配置
- テキスト色 `#D2D2D2`、フォントサイズ `14px`、行高 `28px`、左右パディング `8px`
- アクティブタブは Bold 表示
- クリックでタブ切り替え
- **ビルド確認**

### Step 5: Todo リスト
- タブに応じてフィルタリング（All / Active / Completed）
- 各アイテム: 背景 `#2A2A2A`、高さ `35px`、パディング `10px`、角丸 `4px`、マージンボトム `5px`
- チェックボックス: 円形 16px、ボーダー `#D9D9D9`、チェック済み → `#5DC2AF`
- チェックボックスクリックで `is_completed` をトグル
- 完了タスクにはテキスト打ち消し線を表示
- スクロール対応
- **ビルド確認**

### Step 6: ファイル分割
フレームワークの慣習に合わせて以下を目安にファイルを分割する:
```
src/
├── main.*           # エントリーポイント + ルートUI
├── data.*           # データモデル
└── (widget|components)/
    ├── input.*      # Input コンポーネント
    ├── tabs.*       # Tab メニュー
    └── todo_item.*  # Todo アイテム / リスト
```
- **ビルド確認**

## 実装時の共通ルール

- デザイントークンは定数として一箇所にまとめる
- 各ステップはプレースホルダー方式で進める（未実装部分を残しつつビルドを通す）
- コンパイルエラーはその場で修正してから次のステップへ
- フレームワーク固有の落とし穴は `ai_docs/step-implementation-guide.md` を参照

## デザイントークン早見表

> 詳細・最新値は必ず `design/tokens.md` を参照すること。

### Colors

| トークン | 値 | 用途 |
|----------|----|------|
| `C_BG` | `#1C1C1C` | ウィンドウ背景 |
| `C_SURFACE` | `#2A2A2A` | Todo アイテム背景 |
| `C_INPUT` | `#303030` | 入力フィールド背景 |
| `C_TEXT` | `#D2D2D2` | 一般テキスト |
| `C_WHITE` | `#FFFFFF` | タイトル・入力テキスト |
| `C_MUTED` | `#9B9B9B` | プレースホルダー・完了テキスト |
| `C_ACCENT` | `#5DC2AF` | フォーカスボーダー・チェック済み |
| `C_CB_BORDER` | `#D9D9D9` | チェックボックスボーダー |

### Spacing & Sizes

| 箇所 | 値 |
|------|----|
| コンテンツ padding | 上下 `10px` / 左右 `24px` |
| Title margin-bottom | `14px` |
| TodoInput margin-bottom | `14px` |
| TabMenu margin-bottom | `3px` |
| TodoItem margin-bottom | `5px` |
| TodoInput height | `35px` |
| TodoInput padding | 上下 `4px` / 左右 `16px` |
| TodoInput border-radius | `4px` |
| TabMenu item padding | 左右 `8px` |
| TabMenu line-height | `28px` |
| TodoItem height | `35px` |
| TodoItem padding | `10px` |
| TodoItem border-radius | `4px` |
| CheckBox size | `16px` |
| CheckBox border-radius | `8px`（円形） |
| CheckBox margin-right | `18px` |