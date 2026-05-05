# Go / therecipe-qt Todo App

## ビルド (Intel Mac のみ)

```bash
# vendor ディレクトリを用意
go mod vendor

# Qt@5 の場所を指定してビルド
QT_DIR=/usr/local/opt/qt5 QT_HOMEBREW=true qtdeploy build desktop .
open deploy/darwin/QtforGo.app
```

## Apple Silicon での制約 (実行不可)

`therecipe/qt` は 2020 年以降メンテナンスが停止しており、Apple Silicon + macOS 14+ では動作しない。

| 問題 | 詳細 |
|------|------|
| アーキテクチャ不一致 | `qtdeploy` が `GOARCH=amd64` を強制。Homebrew の Qt@5 は `arm64` のみ |
| AGL フレームワーク | macOS 10.14 で削除された `AGL.framework` をリンカが要求 |
| `qtdeploy` ハードコード | `cmd.go:720` で `"GOARCH": "amd64"` が強制されており上書き不可 |

`go build ./...` は通る（CGo リンクが走らないため）。

## ファイル構成

```
Go/QtforGo/
├── main.go          # エントリーポイント + MainWindow
├── theme.go         # デザイントークン（initTheme で QApplication 後に初期化）
├── data.go          # Todo, TabFilter, TodoModel, MenuModel
├── todo_input.go    # Input ウィジェット (QLineEdit + QSS)
├── tab_menu.go      # TabMenu (QLabel + ConnectMousePressEvent)
└── todo_list.go     # TodoList (QScrollArea) + TodoItemWidget (ConnectPaintEvent)
```