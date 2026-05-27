# Dioxus Todo

Rust Todo app using [Dioxus](https://dioxuslabs.com/) 0.5 — React-inspired declarative UI framework for desktop.

## Requirements

- Rust (stable) 1.70+

Install Rust on all platforms via https://rustup.rs/:
```sh
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

**Windows**: `winget install Rustlang.Rustup` or download rustup-init.exe from https://rustup.rs/

## Install（Dioxus CLI）

```sh
cargo install dioxus-cli
```

## Run

**Launch as a desktop app (recommended):**

```sh
cargo run
```

**Development mode with hot reload:**

```sh
dx serve --hot-reload --platform desktop
```

## Architecture

React-inspired declarative component structure using Dioxus. State is managed with `use_signal` hooks; components are separated into files.

```
src/
├── main.rs         # entry point · dioxus::launch · root component
├── data.rs         # Todo data model · TabFilter · state type definitions
└── components/     # Dioxus components for input, tabs, and Todo list
```