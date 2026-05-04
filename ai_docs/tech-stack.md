# Tech Stack

各言語・フレームワークの実装一覧。チェック済みは実装完了を示す。

## Dart

| フレームワーク | ステータス | 備考 |
|----------------|-----------|------|
| Flutter | ✅ 実装済み | `window_manager` でウィンドウサイズ制御 |
| Rikulo UI | 🔲 未実装 | |

## Python

| フレームワーク | ステータス | 備考 |
|----------------|-----------|------|
| Flet | ✅ 実装済み | |
| tkinter | ✅ 実装済み | |
| Kivy | ✅ 実装済み | |
| Remi | ✅ 実装済み | Webベース |
| Reflex | ✅ 実装済み | Webベース（旧Pynecone） |
| PyQt | ✅ 実装済み | Qt5/Qt6バインディング |
| TkEasyGUI | ✅ 実装済み | tkinterラッパー |
| Toga | ✅ 実装済み | BeeWareプロジェクト |
| PyForms | ✅ 実装済み | |
| PyGTK | ✅ 実装済み | |
| wxPython | ✅ 実装済み | |
| Azul | 🔲 未実装 | |

## C++

| フレームワーク | ステータス | 備考 |
|----------------|-----------|------|
| QT | ✅ 実装済み | |
| wxWidgets | ✅ 実装済み | |
| GTKmm | ✅ 実装済み | GTK3 C++バインディング |
| FLTK | ✅ 実装済み | |
| NanoGUI | ✅ 実装済み | |
| U++ (Ultimate++) | ✅ 実装済み | |
| CEGUI | ✅ 実装済み | |
| Cinder | ✅ 実装済み | |
| ImGui | ✅ 実装済み | Immediate Mode GUI |
| GTK | 🔲 未実装 | |
| Azul | 🔲 未実装 | |

## JavaScript / TypeScript

| フレームワーク | ステータス | 備考 |
|----------------|-----------|------|
| Electron + VanillaJS | ✅ 実装済み | MVC構成 |
| Electron + React | ✅ 実装済み | |
| Electron + Vue | ✅ 実装済み | |
| Tauri (Vite) | ✅ 実装済み | Rustバックエンド |
| Neutralino.js | ✅ 実装済み | |
| NW.js | ✅ 実装済み | |
| React Native | ✅ 実装済み | モバイル向け |
| Proton Native | ✅ 実装済み | |
| DeskGap | ✅ 実装済み | |
| Carlo | ✅ 実装済み | Chromeベース |
| Sciter | 🔲 未実装 | |
| Ultralight | 🔲 未実装 | |

## Go

| フレームワーク | ステータス | 備考 |
|----------------|-----------|------|
| Wails | ✅ 実装済み | Vue3フロントエンド |
| Fyne | ✅ 実装済み | |
| Lorca | ✅ 実装済み | Chromeベース |
| Gio | ✅ 実装済み | |
| Go-GTK | ✅ 実装済み | |
| shiny | ✅ 実装済み | |
| Walk | ✅ 実装済み | Windows専用 |
| Qt for Go | 🔲 未実装 (`Go/QtforGo/`) | |
| go-sciter | 🔲 未実装 | |
| nuklear | 🔲 未実装 | |

## Rust

| フレームワーク | ステータス | 備考 |
|----------------|-----------|------|
| Slint | ✅ 実装済み | DSLベースUI定義 |
| Tauri | ✅ 実装済み | JavaScriptと共通 |
| Iced | ✅ 実装済み | Elm-likeアーキテクチャ |
| Dioxus | ✅ 実装済み | React-likeアーキテクチャ |
| egui | ✅ 実装済み | Immediate Mode |
| gtk-rs | ✅ 実装済み | |
| fltk-rs | ✅ 実装済み | |
| Relm4 | ✅ 実装済み | GTKベース |
| vizia | ✅ 実装済み | |
| rui | ✅ 実装済み | |
| Druid | ✅ 実装済み | （現在アーカイブ済みフレームワーク） |
| OrbTk | ✅ 実装済み | （現在アーカイブ済みフレームワーク） |
| Xilem | 🔲 未実装 | Druid後継 |
| KAS | 🔲 未実装 | |
| Conrod | 🔲 未実装 | |
| Azul | 🔲 未実装 | |
| Leptos | 🔲 未実装 | WebAssembly向け |

## C#

| フレームワーク | ステータス | 備考 |
|----------------|-----------|------|
| Avalonia | ✅ 実装済み | クロスプラットフォーム |
| Uno Platform | ✅ 実装済み | UWP互換 |
| MAUI | ✅ 実装済み | .NET MAUI |
| WPF | ✅ 実装済み | Windows専用 |
| Prism | ✅ 実装済み | WPF向けMVVMフレームワーク |
| UWP | 🔲 未実装 | |
| Xamarin.Forms | 🔲 未実装 | |
| WinForms | 🔲 未実装 | |
| GTK# | 🔲 未実装 | |
| Electron.NET | 🔲 未実装 | |
| OpenTK | 🔲 未実装 | |

## Common Dependencies

| 役割 | ライブラリ例 |
|------|-------------|
| ウィンドウサイズ制御 | `window_manager` (Flutter), Wails設定, Electronの `BrowserWindow` |
| フロントエンドビルド | Vite (Tauri, Wails), webpack (Electron) |
| パッケージ管理 | pub (Dart), Cargo (Rust), go.mod (Go), npm/yarn (JS), pip (Python), NuGet (C#) |