# GTK# Todo

C# Todo app using [GtkSharp](https://github.com/GtkSharp/GtkSharp) (GTK3 bindings for .NET).

## Requirements

- .NET SDK 8.0+
- GTK3

**macOS**
```sh
brew install dotnet@8 gtk+3
```

**Windows**
```sh
winget install Microsoft.DotNet.SDK.8
```
Install GTK3 via MSYS2: `pacman -S mingw-w64-x86_64-gtk3`

**Linux (Ubuntu/Debian)**
```sh
sudo apt install dotnet-sdk-8.0 libgtk-3-dev
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

A simple near-single-file structure. GTK3 widgets are assembled directly, with the data model and UI logic managed in C# classes.

| Layer | File/Directory | Role |
|-------|----------------|------|
| Model | `src/Models/` | Todo data · state model |
| View | `src/Views/` | UI structure via GtkSharp widgets |
| Components | `src/Components/` | input field · tabs · list components |
| Entry | `src/Program.cs` | app launch · window initialization |