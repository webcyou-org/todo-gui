# egui Todo

Rust Todo app using [egui](https://github.com/emilk/egui) / [eframe](https://github.com/emilk/egui/tree/master/crates/eframe) — immediate mode GUI library.

## Requirements

- Rust (stable) 1.70+

Install Rust on all platforms via https://rustup.rs/:
```sh
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
rustup update
```

**Windows**: `winget install Rustlang.Rustup` or download rustup-init.exe from https://rustup.rs/

**Linux** — additional dependencies:

```sh
sudo apt-get install libxcb-render0-dev libxcb-shape0-dev libxcb-xfixes0-dev libxkbcommon-dev libssl-dev
```

## Build & Run

```sh
cargo run --release
```

## Architecture

egui's immediate mode GUI pattern. The `update` function is called every frame to declaratively render the UI; state is centrally managed in the `App` struct.

```
src/
├── main.rs         # entry point · eframe::run_native · App launch
├── lib.rs          # App struct · eframe::App implementation (update function)
├── data.rs         # Todo data model · TabFilter · state management
├── app.rs          # UI rendering logic (egui widget calls)
└── theme.rs        # color and style constants
```