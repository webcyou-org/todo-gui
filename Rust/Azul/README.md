# Azul Todo

Rust Todo app using [Azul](https://azul.rs/) — a functional, reactive GUI framework built on Mozilla WebRender.

> **Note: Building on macOS ARM64 (Apple Silicon) requires additional steps.**
> See [Notes](#notes) for details.

## Requirements

- Rust (stable) 1.70+

## Build & Run

```sh
cargo run
```

Production build:

```sh
cargo build --release
```

## File Structure

```
src/
├── main.rs              # entry point + layout() + window setup
├── data.rs              # data model (Todo, TabFilter, AppState, ToggleData)
├── theme.rs             # design token constants
└── components/
    ├── mod.rs
    ├── input.rs         # Input component + Enter key add logic
    ├── tabs.rs          # Tab menu (All / Active / Completed)
    └── todo_list.rs     # TodoItem + TodoList + checkbox toggle
```

## Architecture

MVC pattern. State is managed via Azul's `extern "C"` callbacks and `RefAny` type erasure.

| Layer | File | Role |
|-------|------|------|
| Model | `src/data.rs` | state management · business logic |
| View | `src/main.rs`, `src/components/` | DOM construction · `layout()` function |
| Controller | `extern "C"` callback functions | event → AppState update |

## Notes

### Building on macOS ARM64

Azul 1.0.0-alpha4 assumes dynamic linking against pre-built binaries, but no macOS ARM64 binary is included in the official release. This implementation builds using **git source + the `link-static` feature**.

The `link-static` build requires **generated code** (`dll_api_static.rs`). Run the following steps before the first build:

```sh
# 1. Clone the azul repository
git clone https://github.com/fschutt/azul /tmp/azul-src

# 2. Run the code generator
cd /tmp/azul-src/doc && cargo run --release -- codegen all

# 3. Copy the generated files to the cargo git cache
AZUL_CHECKOUT=$(ls -d ~/.cargo/git/checkouts/azul-*/e57d9e9*/ 2>/dev/null | head -1)
mkdir -p "$AZUL_CHECKOUT/target/codegen/v2"
cp /tmp/azul-src/target/codegen/v2/dll_api_static.rs  "$AZUL_CHECKOUT/target/codegen/v2/"
cp /tmp/azul-src/target/codegen/v2/dll_api_build.rs   "$AZUL_CHECKOUT/target/codegen/v2/"
cp /tmp/azul-src/target/codegen/v2/dll_api_dynamic.rs "$AZUL_CHECKOUT/target/codegen/v2/"
cp /tmp/azul-src/target/codegen/v2/reexports.rs       "$AZUL_CHECKOUT/target/codegen/v2/"

# 4. Build normally
cargo run
```

### Azul-specific notes

- `azul 0.1.0` (crates.io) is a name-reservation stub — do not use
- `link-static` builds WebRender and 263 other packages together; the first build takes several minutes
- `extern "C"` callbacks are required: all Azul state is passed via `RefAny` type erasure
- To pass individual state to multiple items, nest a wrapper like `ToggleData { app: RefAny, id: usize }` inside `RefAny`
- `AzString::from("literal")` may be needed to explicitly resolve `Into<AzString>` type inference
- `with_inline_style(&format!(...))` causes a type error — pass via `.as_str()` or a variable instead
- `TextInputState`, `OnTextInputReturn`, `TextInputValid`, `CheckBoxState` are imported from `azul::widgets`
- `VirtualKeyCode` is imported from `azul::dom`