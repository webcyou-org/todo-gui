# UWP Todo

C# Todo app using [UWP](https://learn.microsoft.com/windows/uwp/) (Universal Windows Platform).

> **Windows 専用** — UWP は Windows でのみ動作します。

## Requirements

- Windows 10/11
- Visual Studio 2022 with "Universal Windows Platform development" workload

## Build & Run

Visual Studio で `ToDo.sln` を開き、**F5** でビルド・実行してください。

## Architecture

UWP の MVVM パターン。XAML ページが View を担い、ViewModel が INotifyPropertyChanged でデータバインディングを提供する。

| レイヤー | ファイル | 役割 |
|---------|---------|------|
| Model | `ToDo/Models/Todo.cs` | Todo データモデル |
| ViewModel | `ToDo/ViewModels/MainViewModel.cs` | 状態管理・コマンド定義 |
| View | `ToDo/MainPage.xaml`, `ToDo/Converters/` | UWP XAML UI・値コンバーター |
| Entry | `ToDo/App.xaml.cs` | アプリ起動・ナビゲーション設定 |