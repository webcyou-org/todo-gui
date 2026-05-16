# egui Todo

Rust Todo app using [egui](https://github.com/emilk/egui) / [eframe](https://github.com/emilk/egui/tree/master/crates/eframe) — immediate mode GUI library.

## Requirements

- Rust (stable) 1.70+

```sh
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
rustup update
```

**Linux** の場合は追加で:

```sh
sudo apt-get install libxcb-render0-dev libxcb-shape0-dev libxcb-xfixes0-dev libxkbcommon-dev libssl-dev
```

## Build & Run

```sh
cargo run --release
```