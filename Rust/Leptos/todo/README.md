# Leptos Todo

Rust + [Leptos](https://leptos.dev/) (v0.6) Todo app. Runs in the browser via WebAssembly (CSR).

## Requirements

- Rust (stable)
- `wasm32-unknown-unknown` target
- `trunk` build tool

```sh
rustup target add wasm32-unknown-unknown
cargo install trunk
```

## Run

```sh
trunk serve
```

Open `http://localhost:8080` in a browser.

## Build

```sh
trunk build --release
```

Outputs optimized WASM + HTML to `dist/`.

## File Structure

```
src/
├── lib.rs               # App component + CSS + entry point
├── data.rs              # data model (Todo / TabFilter)
└── components/
    ├── mod.rs
    ├── input.rs         # TodoInput component
    ├── tabs.rs          # TabMenu component
    └── todo_list.rs     # TodoList component
```

## Architecture

MVVM pattern. Leptos reactive signals serve as the ViewModel.

| Layer | File | Role |
|-------|------|------|
| Model | `data.rs` | data structures · business logic |
| ViewModel | `lib.rs` (App) | state management via `RwSignal` |
| View | `components/` | UI rendering · event handling |

## Notes

- Leptos CSR requires `[lib] crate-type = ["cdylib", "rlib"]` and `src/lib.rs`
- State signals (`RwSignal<T>`) are `Copy` so they can be passed directly as component props
- Use `create_memo` to derive the filtered list and `For` component for efficient diffing
- Focus border handled via CSS `:focus` pseudo-class (far simpler than Druid)
- Strikethrough achieved with a single CSS line: `text-decoration: line-through`