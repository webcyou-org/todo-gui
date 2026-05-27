# Freya Todo

Rust Todo app using [Freya](https://freyaui.dev/) 0.3.4 — cross-platform native GUI library powered by Skia and Dioxus.

## Requirements

- Rust (stable) 1.70+
- macOS, Windows, or Linux

```sh
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

## Run

```sh
cargo run
```

## File Structure

```
src/
├── main.rs              # entry point + root component
├── data.rs              # data model (Todo, TabFilter)
├── theme.rs             # design token constants
└── components/
    ├── mod.rs
    ├── input.rs         # TodoInput component
    ├── tabs.rs          # TabMenu component
    └── todo_list.rs     # TodoList + TodoItem components
```

## Architecture

MVC pattern. State is reactively managed with Freya's RSX macros and `use_signal`.

| Layer | File | Role |
|-------|------|------|
| Model | `data.rs` | state management · business logic |
| View | `components/` | UI rendering · event handling |
| Controller | `main.rs` | bridging input → Signal |

## Notes

- The Enter key is captured by the root `rect` via the `onglobalkeydown` event
- Input styling overrides background color, border, and focus color via `InputThemeWith`
- Checkbox is rendered as a circle using a `rect` with `corner_radius: "8"`
- Text strikethrough uses the `decoration: "line-through"` attribute on `label`
- Border format: `"<width> inner/outer/center <color>"` (no CSS `solid` keyword)
- The `fill` size unit fills all remaining available space (`fill-available` is invalid)