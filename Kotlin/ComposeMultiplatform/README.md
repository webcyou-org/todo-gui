# Kotlin Compose Multiplatform Todo

Kotlin Todo app using [Compose Multiplatform](https://www.jetbrains.com/compose-multiplatform/) for Desktop.

## Requirements

- JDK 21+
- Gradle 8.10.2 (Wrapper 同梱)

```sh
brew install openjdk@21
```

## Run

```sh
JAVA_HOME=$(/usr/libexec/java_home -v 21) ./gradlew run
```

## Build (配布バイナリ)

```sh
JAVA_HOME=$(/usr/libexec/java_home -v 21) ./gradlew package
# 出力先: build/compose/binaries/
```
