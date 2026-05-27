# Makepad Todo

Rust Todo app using [Makepad](https://github.com/makepad/makepad) 1.0 — GPU-accelerated live-design UI framework.

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

Production build:

```sh
cargo build --release
./target/release/todo
```

> To enable hot reload, nightly is required:
> ```sh
> MAKEPAD=lines cargo +nightly run
> ```

## Architecture

Two-layer structure: UI layout and style declared with Makepad's `live_design!` DSL, logic implemented in Rust via the `MatchEvent` / `Widget` traits. Custom widgets are defined with `#[derive(Live, LiveHook, Widget)]`.

```
src/
├── main.rs                 # entry point · App widget · live_design · event handling
├── data.rs                 # Todo · TabFilter · AppData data model
└── components/
    ├── mod.rs
    └── todo_list.rs        # TodoList custom widget (PortalList-based)
```