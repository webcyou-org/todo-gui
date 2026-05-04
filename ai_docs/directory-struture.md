# Directory Structure

## Root

```
todo-gui/
├── ai_docs/               # AIアシスタント向けプロジェクトドキュメント
├── design/                # デザインアセット
│   ├── ToDoAPP.fig        # Figmaデザインファイル
│   └── todo@1.png         # UIスクリーンショット（デザイン参照画像）
├── C#/                    # C#実装群
├── C++/                   # C++実装群
├── Dart/                  # Dart実装群
├── Go/                    # Go実装群
├── JavaScript/            # JavaScript実装群
├── Python/                # Python実装群
├── Rust/                  # Rust実装群
├── README.md
└── LICENSE
```

## Language / Framework Directories

### C# (`C#/`)

```
C#/
├── Avalonia/ToDo/
├── MAUI/ToDo/
├── Prism/
├── UnoPlatform/ToDo/
└── WPF/
```

### C++ (`C++/`)

```
C++/
├── CEGUI/
├── Cinder/
├── FLTK/
├── GTKmm/
├── ImGui/
├── NanoGUI/
├── QT/
├── U++/
└── wxWidgets/
```

### Dart (`Dart/`)

```
Dart/
└── Flutter/
    └── todo/
        ├── lib/
        │   └── main.dart   # アプリエントリーポイント（StatefulWidget構成）
        ├── macos/
        ├── pubspec.yaml
        └── README.md
```

### Go (`Go/`)

```
Go/
├── Fyne/
├── Gio/
├── Go-GTK/
├── Lorca/
├── QtforGo/
├── Wails/
│   └── todo/
│       ├── app.go          # バックエンドロジック
│       ├── main.go         # エントリーポイント
│       ├── frontend/       # Vue3 + TypeScript フロントエンド
│       │   └── src/
│       │       ├── App.vue
│       │       └── components/
│       └── wails.json
├── Walk/
└── shiny/
```

### JavaScript (`JavaScript/`)

```
JavaScript/
├── Carlo/todo/
├── DeskGap/todo/
├── Electron/
│   ├── VanillaJS/
│   │   └── todo/
│   │       ├── index.html
│   │       ├── main.js         # Electronメインプロセス
│   │       ├── renderer.js     # レンダラープロセス
│   │       └── src/js/
│   │           ├── AppController.js
│   │           ├── Model/
│   │           │   ├── TodoModel.js
│   │           │   └── MenuModel.js
│   │           ├── component/
│   │           │   ├── todoComponent.js
│   │           │   └── menuComponent.js
│   │           └── const/
│   │               ├── todoData.js
│   │               └── tabMenuData.js
│   ├── React/
│   └── Vue/
├── NWjs/
├── Neutralinojs/todo/
├── ProtonNative/todo/
├── ReactNative/todo/
└── tauri/vite/
```

### Python (`Python/`)

```
Python/
├── Flet/
├── Kivy/
├── PyForms/
├── PyGTK/
├── TkEasyGUI/
├── Toga/
├── pyqt/
├── reflex/todo/
├── remi/
├── tkinter/
└── wxPython/
```

### Rust (`Rust/`)

```
Rust/
├── Dioxus/todo/
├── Druid/todo/
├── Iced/todo/
├── OrbTk/
├── Relm4/todo/
├── Slint/todo/
│   ├── src/
│   └── ui/
├── egui/
├── fltk-rs/todo/
├── gtk-rs/todo/
├── rui/todo/
└── vizia/todo/
```

## Naming Convention

各実装ディレクトリ内の一般的な構成パターン:

```
<Framework>/
├── src/          # ソースコード
├── main.*        # エントリーポイント
├── README.md     # フレームワーク固有のセットアップ手順
└── <build-files> # Cargo.toml / go.mod / pubspec.yaml / package.json など
```