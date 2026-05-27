# Prism Todo

C# Todo app using [Prism](https://prismlibrary.com/) with WPF — MVVM framework for .NET.

> **Windows only** — WPF runs on Windows only.

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

MVVM pattern using the Prism library. The DI container and NavigationService keep the ViewModel and View loosely coupled; commands and bindings separate UI logic.

| Layer | File | Role |
|-------|------|------|
| Model | `Models/TabFilter.cs`, `Todo.cs` | Todo data · filter state |
| ViewModel | `ViewModels/MainWindowViewModel.cs` | command definitions · state management (Prism BindableBase) |
| View | `Views/Controls/`, `MainWindow.xaml` | WPF XAML UI · custom controls |
| Entry | `App.xaml.cs` | Prism app launch · DI configuration |