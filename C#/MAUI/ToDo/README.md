# .NET MAUI Todo

C# Todo app using [.NET MAUI](https://learn.microsoft.com/dotnet/maui/) — multi-platform app UI.

## Requirements

- .NET SDK 8.0+ with MAUI workload
- macOS: Xcode インストール済み

```sh
# MAUI workload のインストール
dotnet workload install maui
```

## Install

```sh
dotnet restore ToDo/ToDo.csproj
```

## Run

**macOS (Mac Catalyst)**:
```sh
dotnet build ToDo/ToDo.csproj -t:Run -f net8.0-maccatalyst
```

**iOS Simulator**:
```sh
dotnet build ToDo/ToDo.csproj -t:Run -f net8.0-ios
```

> Windows では `-f net8.0-windows10.0.19041.0` を指定してください。

## Architecture

.NET MAUI の MVVM パターンを採用。XAML で UI を記述し、ViewModel がデータバインディングを介して Model と連携する。複数プラットフォームに単一コードベースで対応する。

| レイヤー | ファイル | 役割 |
|---------|---------|------|
| Model | `ToDo/Todo.cs`, `TabFilter.cs` | Todo データ・フィルター状態 |
| ViewModel | — | `MainPage.xaml.cs` がコードビハインドとして UI ロジックを担当 |
| View | `ToDo/MainPage.xaml`, `AppShell.xaml` | MAUI XAML による UI 定義 |
| Entry | `ToDo/MauiProgram.cs` | アプリ起動・サービス登録 |