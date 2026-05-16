# Walk Todo

Go Todo app using [Walk](https://github.com/lxn/walk) — Windows 専用 Go GUI ライブラリ。

> **Windows 専用** — Windows 環境でのみビルド・実行できます。

## Requirements

- Windows
- Go 1.23+

## Run

### 1. rsrc ツールのインストール（初回のみ）

マニフェストを埋め込むための `rsrc` ツールを取得する。

```powershell
go install github.com/akavel/rsrc@latest
```

### 2. リソースファイルの生成

```powershell
go generate
```

`todo.manifest` から `rsrc.syso` が生成される。

### 3. ビルド & 実行

```powershell
go build -ldflags="-H windowsgui" -o todo.exe .
./todo.exe
```

`-H windowsgui` を付けないとコンソールウィンドウが余分に開く。

## ファイル構成

```
Walk/
├── main.go        # エントリーポイント・MainWindow・UI ロジック
├── data.go        # データモデル（Todo, TabFilter, TodoModel, MenuModel）
├── colors.go      # デザイントークン（walk.Color 定数）
├── todo_row.go    # CustomWidget による Todo 行の描画
├── todo.manifest  # DPI 認識マニフェスト
├── go.mod
└── go.sum
```

## 既知の制約

Walk の Canvas API には `RoundRect` がないため、  
Todo 行の背景は角丸なし（仕様値 `4px` は未対応）。  
入力フィールドのフォーカスボーダーはネイティブ Win32 スタイル。