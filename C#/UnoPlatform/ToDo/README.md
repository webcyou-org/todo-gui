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