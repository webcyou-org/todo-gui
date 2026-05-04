#![allow(non_snake_case)]

mod data;
mod components;

use dioxus::desktop::{Config, WindowBuilder};
use dioxus::desktop::tao::dpi::LogicalSize;
use dioxus::prelude::*;

use data::{TabFilter, Todo};
use components::{TabMenu, TodoInput, TodoList};

// ---------------------------------------------------------------------------
// App
// ---------------------------------------------------------------------------

#[component]
fn App() -> Element {
    let todos      = use_signal(Todo::initial_todos);
    let input      = use_signal(|| String::new());
    let active_tab = use_signal(|| TabFilter::All);
    let next_id    = use_signal(|| 5u64);

    rsx! {
        style {
            "* {{ margin: 0; padding: 0; box-sizing: border-box; font-family: system-ui, sans-serif; }}
             html, body {{ height: 100%; background: #1C1C1C; }}

             .todo-input {{
                 width: 100%; min-width: 430px; height: 35px;
                 padding: 4px 16px; background: #303030; border-radius: 4px;
                 color: #FFFFFF; border: 1px solid transparent; outline: none; font-size: 14px;
             }}
             .todo-input::placeholder {{ color: #9B9B9B; }}
             .todo-input:focus {{ border-color: #5DC2AF; }}

             .tab-btn {{
                 height: 28px; padding: 0 8px; color: #D2D2D2; font-size: 14px;
                 line-height: 28px; background: none; border: none; cursor: pointer;
                 font-weight: normal;
             }}
             .tab-btn.active {{ font-weight: bold; }}

             .todo-list {{ flex: 1; overflow-y: auto; }}
             .todo-item {{
                 display: flex; align-items: center;
                 min-width: 430px; height: 35px; padding: 10px;
                 margin-bottom: 5px; border-radius: 4px;
                 background: #2A2A2A; cursor: pointer;
             }}
             .todo-checkbox {{
                 appearance: none; -webkit-appearance: none;
                 width: 16px; height: 16px; border-radius: 8px;
                 border: 2px solid #D9D9D9;
                 margin-right: 18px; flex-shrink: 0;
                 cursor: pointer; position: relative;
             }}
             .todo-checkbox:checked {{ border-color: #5DC2AF; }}
             .todo-checkbox:checked::before {{
                 content: '';
                 position: absolute; left: 3px; top: -1px;
                 width: 4px; height: 6px;
                 border: 2px solid #5DC2AF;
                 border-top-color: transparent; border-left-color: transparent;
                 transform: rotate(45deg);
             }}
             .todo-text {{ font-size: 14px; color: #D2D2D2; line-height: 20px; }}
             .todo-text.completed {{ text-decoration: line-through; }}"
        }

        div {
            style: "display: flex; flex-direction: column; height: 100vh; padding: 10px 24px; background-color: #1C1C1C;",

            h1 {
                style: "color: #FFFFFF; font-size: 18px; font-weight: bold; margin-bottom: 14px;",
                "ToDo"
            }

            TodoInput { input, todos, next_id }
            TabMenu   { active_tab }
            TodoList  { todos, active_tab }
        }
    }
}

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------

fn main() {
    let config = Config::new()
        .with_window(
            WindowBuilder::new()
                .with_title("ToDo")
                .with_inner_size(LogicalSize::new(800.0_f64, 600.0_f64))
        );

    dioxus::desktop::launch::launch(App, vec![], config);
}