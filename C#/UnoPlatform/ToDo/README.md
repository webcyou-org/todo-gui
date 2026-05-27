# Uno Platform Todo

C# Todo app using [Uno Platform](https://platform.uno/) — cross-platform WinUI 3 / UWP app.

## Requirements

- .NET SDK 8.0+
- Uno Platform template

**macOS**
```sh
brew install dotnet
dotnet workload install uno-wasm-bootstrap
dotnet tool install -g uno.check
uno-check
```

**Windows**
```sh
winget install Microsoft.DotNet.SDK.8
dotnet workload install uno-wasm-bootstrap
dotnet tool install -g uno.check
uno-check
```

**Linux (Ubuntu/Debian)**
```sh
sudo apt install dotnet-sdk-8.0
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

Uno Platform MVVM pattern. The View is written in WinUI 3-compatible XAML, targeting multiple platforms (Desktop / WebAssembly / iOS / Android) from a single codebase.

| Layer | File | Role |
|-------|------|------|
| Model | `ToDo/Models/` | Todo data · state model |
| ViewModel | `ToDo/ViewModels/MainViewModel.cs` | state management · command definitions |
| View | `ToDo/MainPage.xaml`, `ToDo/Converters/` | Uno XAML UI · value converters |
| Entry | `ToDo/App.xaml.cs` | app launch · platform configuration |