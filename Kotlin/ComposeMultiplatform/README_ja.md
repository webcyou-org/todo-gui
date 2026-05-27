# Kotlin Compose Multiplatform Todo

Kotlin Todo app using [Compose Multiplatform](https://www.jetbrains.com/compose-multiplatform/) for Desktop.

## Requirements

- JDK 21+
- Gradle 8.10.2 (Wrapper 同梱)

**macOS**
```sh
brew install openjdk@21
```

**Windows**
```sh
winget install Oracle.JavaRuntimeEnvironment
```
Or download JDK 21 from https://adoptium.net/

**Linux (Ubuntu/Debian)**
```sh
sudo apt install openjdk-21-jdk
```

## Run

**macOS**
```sh
JAVA_HOME=$(/usr/libexec/java_home -v 21) ./gradlew run
```

**Windows / Linux**
```sh
./gradlew run
```

## Build (配布バイナリ)

**macOS**
```sh
JAVA_HOME=$(/usr/libexec/java_home -v 21) ./gradlew package
# 出力先: build/compose/binaries/
```

**Windows / Linux**
```sh
./gradlew package
# 出力先: build/compose/binaries/
```

## Architecture

Compose Multiplatform の宣言的 UI パターン。データモデルを `data/` パッケージで管理し、UI コンポーネントを `ui/` に分離する。`Main.kt` がアプリウィンドウを構築する。

```
src/main/kotlin/
├── Main.kt         # エントリーポイント・application ウィンドウ構築
├── data/
│   └── Model.kt    # Todo データモデル・TabFilter・状態管理
└── ui/
    ├── App.kt      # ルート Composable・レイアウト
    ├── Theme.kt    # カラー・デザイントークン
    └── components/ # TabMenu・TodoInput・TodoList コンポーネント
```
