# Avalonia Todo

C# Todo app using [Avalonia UI](https://avaloniaui.net/) — cross-platform .NET UI framework.

## Requirements

- .NET SDK 8.0+

**macOS**
```sh
brew install dotnet@8
```

**Windows**
```sh
winget install Microsoft.DotNet.SDK.8
```

**Linux (Ubuntu/Debian)**
```sh
sudo apt install dotnet-sdk-8.0
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

MVVM パターンを採用。Avalonia の XAML で View を定義し、ViewModel がコマンドとバインディングを通じて Model と View を仲介する。

| レイヤー | ファイル | 役割 |
|---------|---------|------|
| Model | `Models/TodoItem.cs` | Todo データモデル |
| ViewModel | `ViewModels/MainViewModel.cs` | 状態管理・コマンド定義 |
| View | `Views/TabMenuView.axaml`, `TodoInputView.axaml`, `TodoListView.axaml` | Avalonia XAML による UI 描画 |
| Entry | `Program.cs`, `App.axaml.cs` | アプリ起動・ルートウィンドウ設定 |