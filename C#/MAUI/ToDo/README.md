# .NET MAUI Todo

C# Todo app using [.NET MAUI](https://learn.microsoft.com/dotnet/maui/) — multi-platform app UI.

## Requirements

- .NET SDK 8.0+ with MAUI workload

Download .NET SDK from https://dotnet.microsoft.com/download

**macOS** (requires Xcode):
```sh
brew install dotnet
dotnet workload install maui
```

**Windows**
```sh
winget install Microsoft.DotNet.SDK.8
dotnet workload install maui
```

**Linux** — Linux target is not officially supported by .NET MAUI (Windows/macOS only for desktop).

```sh
# Install MAUI workload
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

> On Windows, specify `-f net8.0-windows10.0.19041.0`.

## Architecture

.NET MAUI MVVM pattern. The UI is written in XAML, and the ViewModel communicates with the Model via data bindings. A single codebase targets multiple platforms.

| Layer | File | Role |
|-------|------|------|
| Model | `ToDo/Todo.cs`, `TabFilter.cs` | Todo data · filter state |
| ViewModel | — | `MainPage.xaml.cs` acts as code-behind handling UI logic |
| View | `ToDo/MainPage.xaml`, `AppShell.xaml` | UI definition in MAUI XAML |
| Entry | `ToDo/MauiProgram.cs` | app launch · service registration |