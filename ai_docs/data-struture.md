# Data Structure

## Entities

### Todo

タスク1件を表すエンティティ。

| フィールド | 型 | 説明 |
|------------|-----|------|
| `id` | int | タスクの一意識別子（1始まり連番） |
| `task` | string | タスクのテキスト内容 |
| `isCompleted` | boolean | 完了状態。`false` = 未完了, `true` = 完了 |

```ts
// TypeScript表現
interface Todo {
  id: number;
  task: string;
  isCompleted: boolean;
}
```

### TabMenu

タブメニュー1項目を表すエンティティ。

| フィールド | 型 | 説明 |
|------------|-----|------|
| `text` | string | タブのラベル文字列（"All" / "Active" / "Completed"） |
| `isActive` | boolean | 現在選択中かどうか |

```ts
interface TabMenu {
  text: "All" | "Active" | "Completed";
  isActive: boolean;
}
```

## Models

### TodoModel

Todoリストの状態管理とビジネスロジックを担う。

| メソッド | 引数 | 戻り値 | 説明 |
|----------|------|--------|------|
| `getData()` | - | `Todo[]` | 全タスクを返す |
| `addTodo(task)` | `string` | `void` | タスクを追加する |
| `findById(id)` | `int` | `Todo` | IDでタスクを検索する |
| `changeCompleted(todo)` | `Todo` | `void` | 完了状態をトグルする |
| `getFilteredTodos(tab)` | `TabMenu` | `Todo[]` | タブに応じてフィルタリングして返す |
| `removeData(id)` | `int` | `void` | IDでタスクを削除する |

#### getFilteredTodos のフィルタロジック

```
tab.text == "All"       → list 全件
tab.text == "Active"    → list.filter(todo => !todo.isCompleted)
tab.text == "Completed" → list.filter(todo => todo.isCompleted)
```

### MenuModel

タブメニューの状態管理を担う。

| メソッド | 引数 | 戻り値 | 説明 |
|----------|------|--------|------|
| `setActiveTab(tabItem)` | `TabMenu` | `void` | アクティブタブを切り替える |
| `getActiveTab()` | - | `TabMenu` | 現在のアクティブタブを返す |
| `getTabList()` | - | `TabMenu[]` | 全タブリストを返す |

## Initial / Default Data

### defaultTodoData

```json
[
  { "task": "Task1", "isCompleted": false },
  { "task": "Task2", "isCompleted": true },
  { "task": "Task3", "isCompleted": false },
  { "task": "Task4", "isCompleted": false }
]
```

### tabMenuData

```json
[
  { "text": "All",       "isActive": true  },
  { "text": "Active",    "isActive": false },
  { "text": "Completed", "isActive": false }
]
```

## State Transitions

```
[Todo追加]
  list: [] → [..., { id: N+1, task: input, isCompleted: false }]

[完了トグル]
  todo.isCompleted: false → true  (完了)
  todo.isCompleted: true  → false (未完了に戻す)

[タブ切替]
  MenuModel.activeTab: "All" → "Active" → "Completed" → "All" ...
  TodoModel.getFilteredTodos(activeTab) で表示リスト再計算
```