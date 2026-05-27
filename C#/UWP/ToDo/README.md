# UWP Todo

C# Todo app using [UWP](https://learn.microsoft.com/windows/uwp/) (Universal Windows Platform).

> **Windows only** — UWP runs on Windows only.

## Requirements

- Windows 10/11
- Visual Studio 2022 with "Universal Windows Platform development" workload

Download Visual Studio from https://visualstudio.microsoft.com/

## Build & Run

Open `ToDo.sln` in Visual Studio and press **F5** to build and run.

## Architecture

UWP MVVM pattern. XAML pages handle the View, and the ViewModel provides data bindings via INotifyPropertyChanged.

| Layer | File | Role |
|-------|------|------|
| Model | `ToDo/Models/Todo.cs` | Todo data model |
| ViewModel | `ToDo/ViewModels/MainViewModel.cs` | state management · command definitions |
| View | `ToDo/MainPage.xaml`, `ToDo/Converters/` | UWP XAML UI · value converters |
| Entry | `ToDo/App.xaml.cs` | app launch · navigation configuration |