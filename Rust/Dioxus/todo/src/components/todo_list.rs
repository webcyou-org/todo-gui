use dioxus::prelude::*;
use crate::data::{TabFilter, Todo};

#[component]
pub fn TodoList(mut todos: Signal<Vec<Todo>>, active_tab: Signal<TabFilter>) -> Element {
    let filtered: Vec<Todo> = todos.read()
        .iter()
        .filter(|t| active_tab.read().matches(t))
        .cloned()
        .collect();

    rsx! {
        div {
            class: "todo-list",
            for todo in filtered.into_iter() {
                TodoItem { todo, todos }
            }
        }
    }
}

#[component]
fn TodoItem(todo: Todo, mut todos: Signal<Vec<Todo>>) -> Element {
    let id        = todo.id;
    let completed = todo.is_completed;
    let task      = todo.task.clone();

    rsx! {
        div {
            key: "{id}",
            class: "todo-item",
            input {
                class: "todo-checkbox",
                r#type: "checkbox",
                checked: completed,
                // Signal は Copy なのでクロージャごとにキャプチャできる
                onchange: move |_| {
                    if let Some(t) = todos.write().iter_mut().find(|t| t.id == id) {
                        t.is_completed = !t.is_completed;
                    }
                },
            }
            span {
                class: if completed { "todo-text completed" } else { "todo-text" },
                "{task}"
            }
        }
    }
}