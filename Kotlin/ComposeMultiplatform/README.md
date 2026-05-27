# Kotlin Compose Multiplatform Todo

Kotlin Todo app using [Compose Multiplatform](https://www.jetbrains.com/compose-multiplatform/) for Desktop.

## Requirements

- JDK 21+
- Gradle 8.10.2 (Wrapper included)

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

## Build (distribution binary)

**macOS**
```sh
JAVA_HOME=$(/usr/libexec/java_home -v 21) ./gradlew package
# Output: build/compose/binaries/
```

**Windows / Linux**
```sh
./gradlew package
# Output: build/compose/binaries/
```

## Architecture

Compose Multiplatform's declarative UI pattern. The data model is managed in the `data/` package, and UI components are separated into `ui/`. `Main.kt` constructs the app window.

```
src/main/kotlin/
├── Main.kt         # entry point · application window construction
├── data/
│   └── Model.kt    # Todo data model · TabFilter · state management
└── ui/
    ├── App.kt      # root Composable · layout
    ├── Theme.kt    # color and design tokens
    └── components/ # TabMenu · TodoInput · TodoList components
```