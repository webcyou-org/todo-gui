# Xamarin.Forms Todo

C# Todo app using [Xamarin.Forms](https://learn.microsoft.com/xamarin/xamarin-forms/) targeting macOS via Xamarin.Mac.

> A CHIP.framework stub is required for macOS builds (see `stub_frameworks/`).

## Requirements

- macOS or Windows
- macOS: Visual Studio for Mac or .NET SDK + Xamarin workload + Xcode
- Windows: Visual Studio 2022 with Xamarin workload

Download Visual Studio: https://visualstudio.microsoft.com/

## Install

Copy `stub_frameworks/CHIP.framework` to `/Library/Frameworks/` (workaround for Xcode 26 / macOS 26 SDK):

```sh
sudo cp -R ../stub_frameworks/CHIP.framework /Library/Frameworks/
```

## Build & Run

Open `ToDo.sln` in Visual Studio for Mac, select the **ToDo.macOS** target, and run.

Or via CLI:
```sh
cd ToDo.macOS
msbuild /p:Configuration=Debug
```

## Architecture

Xamarin.Forms MVVM pattern. The shared UI is defined in XAML, and the ViewModel provides bindings via INotifyPropertyChanged. The `ToDo.macOS` project handles platform-specific code.

| Layer | File | Role |
|-------|------|------|
| Model | `ToDo/Models/TodoItem.cs` | Todo data model |
| ViewModel | `ToDo/ViewModels/MainViewModel.cs`, `RelayCommand.cs` | state management · command definitions |
| View | `ToDo/Views/MainPage.xaml`, `TabMenuView.xaml`, `TodoInputView.xaml`, `TodoListView.xaml` | Xamarin.Forms XAML UI |
| Platform | `ToDo.macOS/` | macOS native launch · entry point |