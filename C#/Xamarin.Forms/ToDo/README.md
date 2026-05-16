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

## Architecture

Xamarin.Forms の MVVM パターン。XAML で共有 UI を定義し、ViewModel が INotifyPropertyChanged でバインディングを提供する。プラットフォーム固有処理は `ToDo.macOS` プロジェクトが担当する。

| レイヤー | ファイル | 役割 |
|---------|---------|------|
| Model | `ToDo/Models/TodoItem.cs` | Todo データモデル |
| ViewModel | `ToDo/ViewModels/MainViewModel.cs`, `RelayCommand.cs` | 状態管理・コマンド定義 |
| View | `ToDo/Views/MainPage.xaml`, `TabMenuView.xaml`, `TodoInputView.xaml`, `TodoListView.xaml` | Xamarin.Forms XAML UI |
| Platform | `ToDo.macOS/` | macOS ネイティブ起動・エントリポイント |