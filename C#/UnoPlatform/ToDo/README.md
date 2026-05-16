# Uno Platform Todo

C# Todo app using [Uno Platform](https://platform.uno/) — cross-platform WinUI 3 / UWP app.

## Requirements

- .NET SDK 8.0+
- Uno Platform テンプレート

```sh
dotnet workload install uno-wasm-bootstrap
dotnet tool install -g uno.check
uno-check
```

## Install

```sh
dotnet restore ToDo/ToDo.sln
```

## Run

**Desktop (Skia)**:
```sh
cd ToDo
dotnet run -f net8.0-desktop
```

**WebAssembly**:
```sh
cd ToDo
dotnet run -f net8.0-browserwasm
```

## Architecture

Uno Platform の MVVM パターン。WinUI 3 互換の XAML で View を記述し、複数ターゲット（Desktop / WebAssembly / iOS / Android）に単一コードで対応する。

| レイヤー | ファイル | 役割 |
|---------|---------|------|
| Model | `ToDo/Models/` | Todo データ・状態モデル |
| ViewModel | `ToDo/ViewModels/MainViewModel.cs` | 状態管理・コマンド定義 |
| View | `ToDo/MainPage.xaml`, `ToDo/Converters/` | Uno XAML UI・値コンバーター |
| Entry | `ToDo/App.xaml.cs` | アプリ起動・プラットフォーム設定 |