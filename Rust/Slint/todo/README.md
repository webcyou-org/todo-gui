# Slint Todo

Rust Todo app using [Slint](https://slint.rs/) 1.7 — declarative UI framework with `.slint` markup.

## Requirements

- Rust (stable) 1.70+

Install Rust on all platforms via https://rustup.rs/:
```sh
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

**Windows**: `winget install Rustlang.Rustup` or download rustup-init.exe from https://rustup.rs/

## Build & Run

```sh
cargo run
```

> The UI is defined in `.slint` files under `ui/`.  
> Install the [Slint VS Code extension](https://marketplace.visualstudio.com/items?itemName=Slint.slint) for live preview support.

## Architecture

Two-layer structure: declarative Slint markup and Rust logic. The UI is defined in `.slint` files; state is bound from Rust via code-generated types produced by `build.rs`.

```
ui/                     # Slint markup (UI definitions)
├── appwindow.slint     # main window · layout
├── types.slint         # shared type definitions
└── components/         # Slint components for input, tabs, and Todo rows
src/                    # Rust logic
├── main.rs             # entry point · Slint window launch · callback registration
├── app.rs              # application logic · state management
└── data.rs             # Todo data model · TabFilter
```