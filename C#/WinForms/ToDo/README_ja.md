# WinForms Todo

C# Todo app using [Windows Forms](https://learn.microsoft.com/dotnet/desktop/winforms/) (.NET WinForms).

> **Windows 専用** — WinForms は Windows でのみ動作します。

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

WinForms のコードビハインド構成。データモデルをシンプルなクラスで管理し、Form イベントハンドラーが UI ロジックを担当する。

| レイヤー | ファイル | 役割 |
|---------|---------|------|
| Model | `Models/Todo.cs`, `TodoModel.cs` | Todo データ・リスト管理 |
| View | `Views/MainForm.cs`, `Views/Controls/` | WinForms UI・カスタムコントロール |
| Entry | `Program.cs` | アプリ起動・Form 生成 |
| Theme | `Theme.cs` | カラー定数・デザイントークン |