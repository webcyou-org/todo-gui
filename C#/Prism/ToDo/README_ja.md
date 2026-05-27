# Prism Todo

C# Todo app using [Prism](https://prismlibrary.com/) with WPF — MVVM framework for .NET.

> **Windows 専用** — WPF は Windows でのみ動作します。

## Requirements

- Windows
- .NET SDK 8.0+

```sh
winget install Microsoft.DotNet.SDK.8
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

Prism ライブラリを用いた MVVM パターン。DI コンテナと NavigationService により ViewModel と View を疎結合に保ち、コマンド・バインディングで UI ロジックを分離する。

| レイヤー | ファイル | 役割 |
|---------|---------|------|
| Model | `Models/TabFilter.cs`, `Todo.cs` | Todo データ・フィルター状態 |
| ViewModel | `ViewModels/MainWindowViewModel.cs` | コマンド定義・状態管理 (Prism BindableBase) |
| View | `Views/Controls/`, `MainWindow.xaml` | WPF XAML UI・カスタムコントロール |
| Entry | `App.xaml.cs` | Prism アプリ起動・DI 設定 |