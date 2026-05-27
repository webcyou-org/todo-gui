# WPF Todo

C# Todo app using [WPF](https://learn.microsoft.com/dotnet/desktop/wpf/) (Windows Presentation Foundation).

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

WPF MVVM pattern. The View is defined in XAML, and the ViewModel provides data bindings via INotifyPropertyChanged and RelayCommand.

| Layer | File | Role |
|-------|------|------|
| Model | `Models/TabFilter.cs`, `Todo.cs` | Todo data · filter state |
| ViewModel | `ViewModels/MainViewModel.cs`, `RelayCommand.cs` | state management · command definitions |
| View | `Views/Controls/`, `MainWindow.xaml` | WPF XAML UI · custom controls |
| Entry | `App.xaml.cs` | app launch · root window configuration |