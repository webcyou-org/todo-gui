# SwiftUI Todo

Swift Todo app using [SwiftUI](https://developer.apple.com/xcode/swiftui/) — Apple's declarative UI framework for macOS.

## Requirements

- macOS 14+
- Xcode Command Line Tools または Xcode

```sh
xcode-select --install
```

## Build

```sh
swift build
```

## Run

```sh
swift run
```

または:

```sh
.build/debug/TodoApp
```

## Architecture

SwiftUI の宣言的 View + `@Observable` モデルによる MVVM パターン。状態変化が自動的に View を再描画する。

```
Sources/TodoApp/
├── main.swift          # エントリーポイント・NSApplication 起動
├── Views/              # SwiftUI View（ContentView・TabMenuView・TodoInputView・TodoListView）
└── Models/             # AppState・Todo・TabFilter（@Observable 状態管理）
```