# Requirement

## Overview

複数のGUIフレームワーク・言語で同一のTodoアプリケーションを実装し、各フレームワークの特性を比較するためのリポジトリ。

## Functional Requirements

### 画面構成

| エリア | 説明 |
|--------|------|
| Title | 画面上部に「ToDo」と表示 |
| Input | タスク追加用テキスト入力フィールド |
| Tab Menu | All / Active / Completed の3タブ |
| Todo List | タスク一覧（チェックボックス + テキスト） |

### 機能一覧

#### タスク追加
- テキストフィールドに文字を入力し Enter / Submit でタスクを追加
- 空文字の場合は追加しない
- 追加後、入力フィールドをクリアする
- プレースホルダーテキスト: `Add Task`

#### タスク完了トグル
- チェックボックスをクリックすると `isCompleted` を切り替える
- 完了状態のタスクにはテキスト打ち消し線（strikethrough）を表示する

#### タブフィルタリング
- **All**: 全タスクを表示
- **Active**: `isCompleted = false` のタスクのみ表示
- **Completed**: `isCompleted = true` のタスクのみ表示
- アクティブなタブはボールド（FontBold）で強調表示

#### タスク削除
- `removeData(id)` で特定タスクを削除する（実装任意）

## Non-Functional Requirements

### ウィンドウサイズ
- デフォルトサイズ: **width 800px / height 600px**

### デザイン
- ダークテーマ統一
- デザイントークンはREADMEおよび `design/todo@1.png` を基準とする

### アーキテクチャ
- 最低でも **MV\*\*** パターン（MVC / MVP / MVVM）を採用する
- 各フレームワークのスタイルに合わせて適宜アレンジする

### 言語・フレームワーク
- 各言語・フレームワークで同一UXを再現することを目標とする
- 実装の難易度や制約によりUIの完全一致は必須ではない

## Initial Data

起動時にサンプルデータを表示する（各実装の慣例に従う）:

```
Task 1 (未完了)
Task 2 (完了)
Task 3 (未完了)
Task 4 (未完了)
```