# Xilem Todo

Todo app implemented with Rust/Xilem (0.4).

## Requirements

- Rust 1.82 or later (`use<>` syntax support)
- macOS / Linux / Windows (Xilem is cross-platform via wgpu)

## Build

```sh
cargo build
```

## Run

```sh
cargo run
```

## File Structure

```
src/
├── main.rs              # entry point · app_logic · window setup
├── data.rs              # data model (Todo / TabFilter / AppState)
├── theme.rs             # design token constants (Color constants)
└── components/
    ├── mod.rs           # module declarations
    ├── input.rs         # TodoInput component
    ├── tabs.rs          # TabMenu component
    └── todo_item.rs     # TodoItem row / TodoList component
```

## Architecture

MVC pattern based on Xilem's reactive view tree. `AppState` is the Model, view functions are the View, and `on_enter`/`on_press` closures are the Controller.

| Layer | File | Role |
|-------|------|------|
| Model | `data.rs` | state management · business logic (add_todo / toggle / filtered_todos) |
| View | `components/` | UI rendering (input / tabs / todo_item) |
| Controller | `main.rs` closures | bridging user input → Model |

## Notes

- **`Color::from_rgb8` is `const fn`** so it can be defined as a `const` — centralized in `theme.rs`.
- **`text_color()` returns `Self`, `placeholder_color()` returns `Prop<...>`** — mind the Style trait chain order: call all `Self`-returning methods first, then continue with Style methods.
- **`FlexSpacer::Fixed(n.px())`** requires `use xilem::masonry::properties::types::AsUnit as _;`.
- **`Padding::from_vh(vertical, horizontal)`** sets vertical/horizontal separately (arrays cannot be passed).
- **Circular checkbox** is achieved with `sized_box(button(...)).width(16.px()).height(16.px())` + `.corner_radius(8.)`.
- **Strikethrough** is not supported in Xilem 0.4's high-level `label` API (`StyleProperty::Strikethrough` is Masonry low-level only). Completed tasks are displayed by changing text color to `C_MUTED` (#9B9B9B) as an alternative.
- **Scrolling** is handled with `portal(flex_col(rows))`.
- **`flex_col` default `CrossAxisAlignment` is `Center` (horizontally centered)**. Use `.cross_axis_alignment(CrossAxisAlignment::Fill)` for left alignment (`Stretch` does not exist; `Fill` is correct).