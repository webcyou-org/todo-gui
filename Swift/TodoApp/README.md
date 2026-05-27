# SwiftUI Todo

Swift Todo app using [SwiftUI](https://developer.apple.com/xcode/swiftui/) — Apple's declarative UI framework for macOS.

## Requirements

- macOS 14+
- Xcode Command Line Tools or Xcode

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

Or:

```sh
.build/debug/TodoApp
```

## Architecture

SwiftUI declarative View + `@Observable` model MVVM pattern. State changes automatically re-render Views.

```
Sources/TodoApp/
├── main.swift          # entry point · NSApplication launch
├── Views/              # SwiftUI Views (ContentView · TabMenuView · TodoInputView · TodoListView)
└── Models/             # AppState · Todo · TabFilter (@Observable state management)
```