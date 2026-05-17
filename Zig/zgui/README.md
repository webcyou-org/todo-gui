# Todo — Zig + zgui (Dear ImGui)

Todo application built with [Zig](https://ziglang.org/) 0.16.0 and [zgui](https://github.com/zig-gamedev/zgui) — the Zig binding for [Dear ImGui](https://github.com/ocornut/imgui) — using GLFW + OpenGL3 backend.

## Requirements

- [Zig](https://ziglang.org/) 0.16.0
- [GLFW](https://www.glfw.org/) 3.4

**macOS**
```sh
brew install zig glfw
```

**Windows**
```sh
winget install zig.zig
```
Download GLFW from https://www.glfw.org/download or `winget install GLFW.GLFW`

**Linux (Ubuntu/Debian)**
```sh
sudo apt install libglfw3-dev
```
Install Zig from https://ziglang.org/download/ or `snap install zig --classic --channel 0.16/stable`

## Build

```sh
zig build
```

## Run

```sh
zig build run
```

Or run the built binary directly:

```sh
./zig-out/bin/todo
```

## File Structure

```
src/
├── main.zig              # Entry point, window setup, main loop
├── data.zig              # AppState, Todo, TabFilter
└── components/
    ├── input.zig         # Input field component
    ├── tabs.zig          # Tab menu (All / Active / Completed)
    └── todo_list.zig     # Todo list with custom-drawn items
fonts/
├── Inter.ttf             # Inter variable font (body text)
└── NotoSansJP.ttf        # Noto Sans JP (Japanese text)
```

## Notes

- zgui is fetched via `build.zig.zon` from [zig-gamedev/zgui](https://github.com/zig-gamedev/zgui) (no vendored copy needed)
- The GLFW and OpenGL3 backends are compiled directly from zgui's bundled Dear ImGui source
- Zig 0.16.0 has a `@ptrCast` regression on `?[:0]const u8` in zgui's backend init — worked around by declaring the backend functions as `extern fn` and calling them directly

## Architecture

即時モード GUI パターン。Zig がデータモデルと状態を管理し、zgui（Dear ImGui の Zig バインディング）が GLFW + OpenGL3 で UI を描画する。

```
src/
├── main.zig        # エントリーポイント・GLFW ウィンドウ・zgui 初期化・メインループ
├── data.zig        # AppState・Todo・TabFilter の状態管理
└── components/     # 入力欄・タブ・Todo リストの zgui ウィジェット関数
fonts/              # Inter・Noto Sans JP フォント
```