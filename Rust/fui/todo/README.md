# Todo — Rust + fui

Todo application built with [Rust](https://www.rust-lang.org/) and [fui](https://github.com/marek-g/rust-fui) — an MVVM GUI framework using Qt windowing and Impeller (Flutter's 2D renderer).

> **macOS Note**: This implementation builds successfully but does **not run on macOS**. The `windowing_qt` backend initializes Qt on a non-main thread, which is prohibited by macOS (NSApplication must be created on the main thread). fui is designed for Linux/Windows.

## Requirements

- [Rust](https://www.rust-lang.org/) (stable)
- Qt 6 (`qtbase`)
- cmake, cbindgen, bindgen

**macOS (build only)**
```sh
brew install qt
```

**Linux (Ubuntu/Debian)**
```sh
sudo apt install qtbase6-dev cmake
cargo install cbindgen
```

**Windows**
Install Qt 6 from https://www.qt.io/download and add to PATH.

## Build

```sh
cargo build
```

## Run (Linux/Windows only)

```sh
cargo run
```

## File Structure

```
src/
├── main.rs              # Entry point, MainViewModel, app loop
├── data.rs              # TabFilter enum
└── components/
    ├── mod.rs           # Module declarations
    ├── input.rs         # Input field + Add button
    ├── tabs.rs          # Tab menu (All / Active / Completed)
    └── todo_item.rs     # Todo list item control
patches/
└── windowing_qt/        # Patched windowing_qt (macOS CMakeLists.txt fix)
```

## Notes

- Uses `[patch.crates-io]` to fix a CMakeLists.txt bug in `windowing_qt 0.17.4` where `KF6::WindowSystem` was unconditionally linked on all platforms (including macOS)
- Uses `impellers = { features = ["prebuilt_libs"] }` (dynamic link) instead of `static_link` because the macOS static binary is missing from the GitHub release
- `typemap 0.3.3` is required by fui internals but contains code deprecated in future Rust editions (harmless warning)

## Architecture

MVVM パターン。`MainViewModel` が状態管理と UI 生成を担い、fui の `Property<T>` と `ObservableVec<T>` でリアクティブなデータバインディングを実現する。

```
src/
├── main.rs         # MainViewModel (ViewModel トレイト実装) + Tokio エントリーポイント
├── data.rs         # TabFilter (All / Active / Completed)
└── components/     # UI パーツ（入力欄・タブ・Todo アイテム）を返す関数
```

fui は Tokio (current_thread) + Qt (windowing) + Impeller (renderer) の 3 層構成。ViewModel は非同期タスクスレッドで動作し、Qt GUI スレッドと内部チャンネルで通信する。