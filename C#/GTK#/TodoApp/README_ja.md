# GTK# Todo

C# Todo app using [GtkSharp](https://github.com/GtkSharp/GtkSharp) (GTK3 bindings for .NET).

## Requirements

- .NET SDK 8.0+
- GTK3

**macOS**
```sh
brew install dotnet@8 gtk+3
```

**Windows**
```sh
winget install Microsoft.DotNet.SDK.8
```
Install GTK3 via MSYS2: `pacman -S mingw-w64-x86_64-gtk3`

**Linux (Ubuntu/Debian)**
```sh
sudo apt install dotnet-sdk-8.0 libgtk-3-dev
```

## Install

```sh
dotnet restore
```

## Run

```sh
dotnet run
```

## Architecture

シングルファイル構成に近いシンプルな構造。GTK3 ウィジェットを直接組み立て、データモデルと UI ロジックを C# クラスで管理する。

| レイヤー | ファイル/ディレクトリ | 役割 |
|---------|---------|------|
| Model | `src/Models/` | Todo データ・状態モデル |
| View | `src/Views/` | GtkSharp ウィジェットによる UI 構成 |
| Components | `src/Components/` | 入力欄・タブ・リストの部品 |
| Entry | `src/Program.cs` | アプリ起動・ウィンドウ初期化 |