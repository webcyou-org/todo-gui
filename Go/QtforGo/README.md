# Go / therecipe-qt Todo App

## Build (Intel Mac only)

```bash
# Prepare vendor directory
go mod vendor

# Build specifying Qt@5 location
QT_DIR=/usr/local/opt/qt5 QT_HOMEBREW=true qtdeploy build desktop .
open deploy/darwin/QtforGo.app
```

## Constraints on Apple Silicon (cannot run)

`therecipe/qt` has not been maintained since 2020 and does not work on Apple Silicon + macOS 14+.

| Issue | Details |
|-------|---------|
| Architecture mismatch | `qtdeploy` forces `GOARCH=amd64`. Homebrew's Qt@5 is arm64 only |
| AGL framework | The linker requires `AGL.framework`, which was removed in macOS 10.14 |
| `qtdeploy` hardcode | `"GOARCH": "amd64"` is forced in `cmd.go:720` and cannot be overridden |

`go build ./...` succeeds (because CGo linking is not invoked).

## File Structure

```
Go/QtforGo/
├── main.go          # entry point + MainWindow
├── theme.go         # design tokens (initialized in initTheme after QApplication)
├── data.go          # Todo, TabFilter, TodoModel, MenuModel
├── todo_input.go    # Input widget (QLineEdit + QSS)
├── tab_menu.go      # TabMenu (QLabel + ConnectMousePressEvent)
└── todo_list.go     # TodoList (QScrollArea) + TodoItemWidget (ConnectPaintEvent)
```

## Architecture

A single-package structure that manipulates Qt5 Widgets from Go via therecipe/qt bindings. Data model and widget components are separated into files; `main.go` constructs the main window.

| Layer | File | Role |
|-------|------|------|
| Model | `data.go` | Todo · TabFilter · TodoModel · MenuModel |
| View | `todo_input.go`, `tab_menu.go`, `todo_list.go` | Qt5 widget components |
| Entry | `main.go` | QApplication startup · MainWindow construction |
| Theme | `theme.go` | design tokens · color constants |