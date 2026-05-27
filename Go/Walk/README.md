# Walk Todo

Go Todo app using [Walk](https://github.com/lxn/walk) — Windows-only Go GUI library.

> **Windows only** — can only be built and run on Windows.

## Requirements

- Windows
- Go 1.23+

## Run

### 1. Install rsrc tool (first time only)

Fetch the `rsrc` tool for embedding the manifest.

```powershell
go install github.com/akavel/rsrc@latest
```

### 2. Generate resource file

```powershell
go generate
```

`rsrc.syso` is generated from `todo.manifest`.

### 3. Build & Run

```powershell
go build -ldflags="-H windowsgui" -o todo.exe .
./todo.exe
```

Without `-H windowsgui`, an extra console window opens.

## File Structure

```
Walk/
├── main.go        # entry point · MainWindow · UI logic
├── data.go        # data model (Todo, TabFilter, TodoModel, MenuModel)
├── colors.go      # design tokens (walk.Color constants)
├── todo_row.go    # Todo row rendering via CustomWidget
├── todo.manifest  # DPI-awareness manifest
├── go.mod
└── go.sum
```

## Known Limitations

Walk's Canvas API has no `RoundRect`,  
so Todo row backgrounds have no rounded corners (the spec value of `4px` is not supported).  
The input field focus border uses the native Win32 style.

## Architecture

A single-package structure that assembles Win32 widgets directly using Walk. Data model and widget components are separated into files; `main.go` constructs the main window.

| Layer | File | Role |
|-------|------|------|
| Model | `data.go` | Todo · TabFilter · TodoModel · MenuModel |
| View | `todo_row.go` | Todo row rendering via CustomWidget |
| Entry | `main.go` | MainWindow construction · UI logic |
| Theme | `colors.go` | walk.Color color constants |