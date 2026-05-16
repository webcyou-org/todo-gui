# .NET MAUI Todo

C# Todo app using [.NET MAUI](https://learn.microsoft.com/dotnet/maui/) — multi-platform app UI.

## Requirements

- .NET SDK 8.0+ with MAUI workload
- macOS: Xcode インストール済み

```sh
# MAUI workload のインストール
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

> Windows では `-f net8.0-windows10.0.19041.0` を指定してください。