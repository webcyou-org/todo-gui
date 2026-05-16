# WPF Todo

C# Todo app using [WPF](https://learn.microsoft.com/dotnet/desktop/wpf/) (Windows Presentation Foundation).

> **Windows 専用** — WPF は Windows でのみ動作します。

## Requirements

- Windows
- .NET SDK 8.0+

## Install

```sh
dotnet restore
```

## Run

```sh
dotnet run
```

## Architecture

WPF の MVVM パターン。XAML で View を定義し、ViewModel が INotifyPropertyChanged と RelayCommand でデータバインディングを提供する。

| レイヤー | ファイル | 役割 |
|---------|---------|------|
| Model | `Models/TabFilter.cs`, `Todo.cs` | Todo データ・フィルター状態 |
| ViewModel | `ViewModels/MainViewModel.cs`, `RelayCommand.cs` | 状態管理・コマンド定義 |
| View | `Views/Controls/`, `MainWindow.xaml` | WPF XAML UI・カスタムコントロール |
| Entry | `App.xaml.cs` | アプリ起動・ルートウィンドウ設定 |