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

MVVM pattern. The View is defined in Avalonia XAML, and the ViewModel mediates between the Model and View via commands and bindings.

| Layer | File | Role |
|-------|------|------|
| Model | `Models/TodoItem.cs` | Todo data model |
| ViewModel | `ViewModels/MainViewModel.cs` | state management · command definitions |
| View | `Views/TabMenuView.axaml`, `TodoInputView.axaml`, `TodoListView.axaml` | UI rendering via Avalonia XAML |
| Entry | `Program.cs`, `App.axaml.cs` | app launch · root window configuration |