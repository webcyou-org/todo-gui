# Xamarin.Forms Todo

C# Todo app using [Xamarin.Forms](https://learn.microsoft.com/xamarin/xamarin-forms/) targeting macOS via Xamarin.Mac.

> macOS ビルドには CHIP.framework スタブが必要です（`stub_frameworks/` を参照）。

## Requirements

- macOS
- Visual Studio for Mac または .NET SDK + Xamarin workload
- Xcode インストール済み

## Install

`stub_frameworks/CHIP.framework` を `/Library/Frameworks/` にコピーしてください（Xcode 26 / macOS 26 SDK 対応のワークアラウンド）:

```sh
sudo cp -R ../stub_frameworks/CHIP.framework /Library/Frameworks/
```

## Build & Run

Visual Studio for Mac で `ToDo.sln` を開き、**ToDo.macOS** ターゲットを選択して実行してください。

または CLI で:
```sh
cd ToDo.macOS
msbuild /p:Configuration=Debug
```