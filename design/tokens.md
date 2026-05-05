# Design Tokens

各フレームワーク実装の **唯一の正** となるデザイン仕様。  
値を変更する場合はここを先に更新し、各実装に反映する。

---

## Colors

| Token | Hex | 用途 |
|-------|-----|------|
| `C_BG` | `#1C1C1C` | ウィンドウ背景 |
| `C_SURFACE` | `#2A2A2A` | Todo アイテム背景 |
| `C_INPUT` | `#303030` | 入力フィールド背景 |
| `C_TEXT` | `#D2D2D2` | 一般テキスト |
| `C_WHITE` | `#FFFFFF` | タイトル・入力テキスト |
| `C_MUTED` | `#9B9B9B` | プレースホルダー・完了テキスト |
| `C_ACCENT` | `#5DC2AF` | アクセント（フォーカスボーダー・チェック済み） |
| `C_CB_BORDER` | `#D9D9D9` | チェックボックスボーダー |

---

## Typography

| Token | 値 | 用途 |
|-------|-----|------|
| `FONT_SIZE_TITLE` | `18px` | タイトル「ToDo」 |
| `FONT_SIZE_NORMAL` | `14px` | 本文・タブ・Todo テキスト |
| `FONT_WEIGHT_TITLE` | Bold | タイトル |
| `FONT_WEIGHT_ACTIVE_TAB` | Bold | アクティブタブ |
| `LINE_HEIGHT_TAB` | `28px` | タブメニュー行高 |

---

## Spacing

### コンテンツ全体

| 方向 | 値 |
|------|----|
| Top / Bottom padding | `10px` |
| Left / Right padding | `24px` |

### コンポーネント間 Margin Bottom

| コンポーネント | 値 |
|----------------|----|
| Title | `14px` |
| TodoInput | `14px` |
| TabMenu | `3px` |
| TodoItem | `5px` |

### コンポーネント内 Padding

| コンポーネント | 値 |
|----------------|----|
| TodoInput | Top/Bottom `4px` / Left/Right `16px` |
| TabMenu アイテム | Left/Right `8px` |
| TodoItem | 全方向 `10px` |

---

## Components

### Window

| プロパティ | 値 |
|-----------|----|
| Width | `800px` |
| Height | `600px` |

### TodoInput

| プロパティ | 値 |
|-----------|----|
| Height | `35px` |
| Min Width | `430px` |
| Border Radius | `4px` |
| Background | `C_INPUT` (`#303030`) |
| Text Color | `C_WHITE` (`#FFFFFF`) |
| Placeholder | `Add Task` |
| Placeholder Color | `C_MUTED` (`#9B9B9B`) |
| Focus Border | `1px solid C_ACCENT` (`#5DC2AF`) |

### TabMenu

| プロパティ | 値 |
|-----------|----|
| Tab Labels | `All` / `Active` / `Completed` |
| Text Color | `C_TEXT` (`#D2D2D2`) |
| Font Size | `14px` |
| Line Height | `28px` |
| Item Padding | Left/Right `8px` |
| Active Style | Font Bold |

### TodoItem

| プロパティ | 値 |
|-----------|----|
| Height | `35px` |
| Min Width | `430px` |
| Background | `C_SURFACE` (`#2A2A2A`) |
| Border Radius | `4px` |
| Padding | `10px` |
| Font Size | `14px` |
| Text Color | `C_TEXT` (`#D2D2D2`) |
| Completed Text Color | `C_MUTED` (`#9B9B9B`) |
| Completed Text Style | Strikethrough |

### CheckBox

| プロパティ | 値 |
|-----------|----|
| Width / Height | `16px` |
| Shape | 円形（`border-radius: 8px`） |
| Border | `2px solid C_CB_BORDER` (`#D9D9D9`) |
| Margin Right | `18px` |
| Checked Background | `C_ACCENT` (`#5DC2AF`) |
| Checked Border | `2px solid C_ACCENT` |

---

## States

| 状態 | 変化 |
|------|------|
| Input: focus | Border `1px solid #5DC2AF` |
| Tab: active | Font Bold |
| Todo: completed | Text strikethrough + Text color → `C_MUTED` |
| Checkbox: checked | Fill `#5DC2AF`、チェックマーク表示 |

---

## 実装ごとの対応表

| Token | Python/tkinter | Python/Kivy | Go/Fyne | Rust/Slint |
|-------|---------------|-------------|---------|------------|
| `C_BG` | `theme.C_BG` | `theme.C_BG` | `apptheme.ColorBG` | `BG: brush` |
| `C_ACCENT` | `theme.C_ACCENT` | `theme.C_ACCENT` | `apptheme.ColorAccent` | `ACCENT: brush` |
| `FONT_SIZE_NORMAL` | `FONT_NORMAL` | `FONT_SIZE_NORMAL` | `AppTheme.Size` | `font-size: 14px` |
| Content Padding | `padx=24, pady=10` | `padding=[24,10]` | `CustomPaddedLayout(10,10,24,24)` | `padding: 10px 24px` |
| Item Height | `height=35` | `height=dp(40)` ⚠️ | `MinSize(0,35)` | `height: 35px` |
| Item Border Radius | Canvas polygon | `RoundedRectangle radius=[dp(4)]` | `CornerRadius=4` | `border-radius: 4px` |
| CheckBox Margin Right | `padx=(10,8)` ⚠️ | `spacing=dp(8)` ⚠️ | `gap=8` ⚠️ | - |

> ⚠️ = 仕様値（`18px`）とズレあり。要修正。

---

## Known Discrepancies（既知のズレ）

実装時に仕様と異なる値が使われている箇所。

| 箇所 | 仕様値 | 現状 | 対象実装 |
|------|--------|------|----------|
| Todo Item Height | `35px` | ✅ 修正済み (`dp(35)`) | Kivy |
| CheckBox Margin Right | `18px` | ✅ 修正済み | tkinter / Kivy / Fyne |
| Input Padding Left/Right | `16px` | ✅ 修正済み | tkinter / Kivy |
| Input Padding Top/Bottom | `4px` | ✅ 修正済み (`dp(4)`) | Kivy |
| Input Padding Left/Right | `16px` | ⚠️ Fyne は Theme API 制約で横縦一括管理 | Fyne |
| Input Padding Top/Bottom | `4px` | ⚠️ Fyne は Theme API 制約で横縦一括管理 | Fyne |