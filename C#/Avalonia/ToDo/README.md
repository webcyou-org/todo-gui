# Avalonia Todo

C# Todo app using [Avalonia UI](https://avaloniaui.net/) — cross-platform .NET UI framework.

## Requirements

- .NET SDK 8.0+

```sh
# .NET SDK のインストール（未インストールの場合）
brew install dotnet@8
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