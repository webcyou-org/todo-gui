# Iced Todo

Rust Todo app using [Iced](https://iced.rs/) 0.12 — cross-platform GUI library inspired by Elm.

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

## Architecture

Iced's Elm architecture (State / Message / Update / View) pattern. State, style, and view are separated into files; immutable state updates drive a reactive UI.

```
src/
├── main.rs         # entry point · iced::run · Application implementation
├── state.rs        # AppState · Todo · TabFilter · Message · update logic
├── view.rs         # view function · Element tree construction
└── style.rs        # custom styles · color constants
```