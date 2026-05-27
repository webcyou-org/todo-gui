# Druid Todo

Rust Todo app using [Druid](https://github.com/linebender/druid) 0.8.3 — data-driven reactive GUI framework.

## Requirements

- Rust (stable) 1.70+

Install Rust on all platforms via https://rustup.rs/:
```sh
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

**Windows**: `winget install Rustlang.Rustup` or download rustup-init.exe from https://rustup.rs/

**Linux (Ubuntu/Debian)** — additional dependencies:
```sh
sudo apt install libgtk-3-dev libcairo2-dev libpango1.0-dev
```

## Build & Run

```sh
cargo run
```

Production build:

```sh
cargo build --release
./target/release/todo
```

## Architecture

Druid's data-driven reactive UI pattern. `AppState` is defined with the `Data` trait; fields are partially referenced via Lens and bound to widgets.

```
src/
├── main.rs         # entry point · AppLauncher · root widget construction
├── data.rs         # AppState · Todo · TabFilter (Druid Data/Lens implementation)
├── lens.rs         # custom Lens definitions
├── theme.rs        # color and style constants
└── widget/         # custom widgets for input, tabs, and Todo list
```