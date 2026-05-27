# WinForms Todo

C# Todo app using [Windows Forms](https://learn.microsoft.com/dotnet/desktop/winforms/) (.NET WinForms).

> **Windows only** — WinForms runs on Windows only.

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

WinForms code-behind structure. The data model is managed in simple classes, and Form event handlers handle UI logic.

| Layer | File | Role |
|-------|------|------|
| Model | `Models/Todo.cs`, `TodoModel.cs` | Todo data · list management |
| View | `Views/MainForm.cs`, `Views/Controls/` | WinForms UI · custom controls |
| Entry | `Program.cs` | app launch · Form creation |
| Theme | `Theme.cs` | color constants · design tokens |