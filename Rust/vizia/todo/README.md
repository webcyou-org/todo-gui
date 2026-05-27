# Vizia Todo

Rust Todo app using [Vizia](https://github.com/vizia/vizia) (git HEAD) — declarative GUI framework with CSS styling.

## Requirements

- Rust (stable) 1.70+

Install Rust on all platforms via https://rustup.rs/:
```sh
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

**Windows**: `winget install Rustlang.Rustup` or download rustup-init.exe from https://rustup.rs/

> Vizia is fetched directly from its git repository (see `Cargo.toml`).

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

Vizia's declarative, reactive UI pattern. State is defined with the `Model` trait; CSS styling and view components are combined.

```
src/
├── main.rs         # entry point · Application launch · root view construction
├── data.rs         # AppState · Todo · TabFilter · Model · Event definitions
├── theme.rs        # color constants
└── components/     # Vizia view parts for input, tabs, and Todo list
```