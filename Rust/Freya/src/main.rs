#![cfg_attr(
    all(not(debug_assertions), target_os = "windows"),
    windows_subsystem = "windows"
)]

mod components;
mod data;
mod theme;

use components::{TabMenu, TodoInput, TodoList};
use data::{default_todos, TabFilter, Todo};
use freya::prelude::*;
use theme::*;

fn main() {
    launch_with_props(app, "ToDo", (800.0, 600.0));
}

fn app() -> Element {
    use_init_theme(|| DARK_THEME);

    let mut todos: Signal<Vec<Todo>> = use_signal(default_todos);
    let mut input_text = use_signal(String::new);
    let mut next_id = use_signal(|| 5usize);
    let active_tab: Signal<TabFilter> = use_signal(|| TabFilter::All);

    let mut add_todo = move || {
        let text = input_text.read().trim().to_string();
        if !text.is_empty() {
            let id = *next_id.read();
            todos.write().push(Todo { id, task: text, is_completed: false });
            *next_id.write() += 1;
            input_text.set(String::new());
        }
    };

    let filtered: Vec<Todo> = todos
        .read()
        .iter()
        .filter(|t| active_tab.read().matches(t))
        .cloned()
        .collect();

    rsx!(
        rect {
            width: "100%",
            height: "100%",
            background: C_BG,
            padding: "10 24",
            direction: "vertical",
            onglobalkeydown: move |e: Event<KeyboardData>| {
                if e.key == Key::Enter {
                    add_todo();
                }
            },

            // Title
            label {
                color: C_WHITE,
                font_size: "18",
                font_weight: "bold",
                margin: "0 0 14 0",
                "ToDo"
            }

            // Input field
            TodoInput {
                value: input_text,
                on_change: move |e: String| {
                    input_text.set(e);
                },
            }

            // Tab menu
            TabMenu {
                active_tab,
            }

            // Todo list
            TodoList {
                todos,
                filtered,
            }
        }
    )
}