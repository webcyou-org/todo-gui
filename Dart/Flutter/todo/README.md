# Flutter Todo

Dart Todo app using [Flutter](https://flutter.dev/) — cross-platform UI toolkit.

![todo](https://user-images.githubusercontent.com/1584153/191999399-373be546-9667-4e0b-92c1-c644bd7ff922.png)

## Requirements

- Flutter SDK 3.x+

**macOS** (requires Xcode)
```sh
brew install flutter
flutter doctor
```

**Windows**
Download Flutter SDK from https://flutter.dev/docs/get-started/install/windows
```sh
flutter doctor
```

**Linux**
```sh
sudo snap install flutter --classic
flutter doctor
```

## Run

**macOS:**

```sh
flutter run -d macos
```

**Other platforms:**

```sh
flutter run -d linux    # Linux
flutter run -d windows  # Windows
flutter run             # select connected device
```

## Architecture

A declarative UI structure using Flutter's widget tree. The data model is managed in `lib/model.dart`; widgets are assembled from a single `main.dart`.

```
lib/
├── main.dart       # entry point · MaterialApp · screen layout
└── model.dart      # Todo data model · state management
```