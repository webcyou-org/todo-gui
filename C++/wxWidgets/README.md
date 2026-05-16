# wxWidgets Todo

C++ Todo app using [wxWidgets](https://www.wxwidgets.org/).  
wxWidgets itself is built from source via CMake ExternalProject (`thirdparty/wxwidgets/`).

## Requirements

- CMake 3.6+
- Xcode Command Line Tools (`xcode-select --install`)
- pkg-config

```sh
brew install cmake pkg-config
```

## Build

初回ビルドは wxWidgets のコンパイルを含むため数分かかります。

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

## Run

```sh
./build/subprojects/Build/todo_core/todo
```