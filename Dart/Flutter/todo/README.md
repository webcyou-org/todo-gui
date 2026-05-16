# Flutter Todo

Dart Todo app using [Flutter](https://flutter.dev/) — cross-platform UI toolkit.

![todo](https://user-images.githubusercontent.com/1584153/191999399-373be546-9667-4e0b-92c1-c644bd7ff922.png)

## Requirements

- Flutter SDK 3.x+
- macOS: Xcode インストール済み

```sh
# Flutter SDK のインストール
brew install flutter
flutter doctor
```

## Run

**macOS:**

```sh
flutter run -d macos
```

**その他のプラットフォーム:**

```sh
flutter run -d linux    # Linux
flutter run -d windows  # Windows
flutter run             # 接続デバイスを選択
```

## Architecture

Flutter のウィジェットツリーによる宣言的 UI 構成。データモデルを `lib/model.dart` で管理し、単一の `main.dart` からウィジェットを組み立てる。

```
lib/
├── main.dart       # エントリーポイント・MaterialApp・画面構成
└── model.dart      # Todo データモデル・状態管理
```
