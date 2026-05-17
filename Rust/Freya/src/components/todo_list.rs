use freya::prelude::*;

use crate::data::Todo;
use crate::theme::*;

#[component]
pub fn TodoList(
    todos: Signal<Vec<Todo>>,
    filtered: Vec<Todo>,
) -> Element {
    rsx!(
        ScrollView {
            width: "100%",
            height: "fill",
            show_scrollbar: true,
            rect {
                width: "100%",
                direction: "vertical",
                spacing: "5",
                for todo in filtered {
                    TodoItem {
                        key: "{todo.id}",
                        todo: todo.clone(),
                        todos,
                    }
                }
            }
        }
    )
}

#[component]
fn TodoItem(todo: Todo, todos: Signal<Vec<Todo>>) -> Element {
    let id = todo.id;
    let is_completed = todo.is_completed;
    let task = todo.task.clone();

    let cb_bg = if is_completed { C_ACCENT } else { "transparent" };
    let cb_border = if is_completed {
        format!("2 inner {C_ACCENT}")
    } else {
        format!("2 inner {C_CB_BORDER}")
    };
    let text_color = if is_completed { C_MUTED } else { C_TEXT };
    let decoration = if is_completed { "line-through" } else { "none" };

    rsx!(
        rect {
            width: "100%",
            height: "35",
            background: C_SURFACE,
            corner_radius: "4",
            padding: "0 10",
            direction: "horizontal",
            cross_align: "center",
            // Checkbox
            rect {
                width: "16",
                height: "16",
                corner_radius: "8",
                background: cb_bg,
                border: "{cb_border}",
                margin: "0 18 0 0",
                onclick: move |_| {
                    if let Some(t) = todos.write().iter_mut().find(|t| t.id == id) {
                        t.is_completed = !t.is_completed;
                    }
                },
            }
            // Task text
            label {
                color: text_color,
                font_size: "14",
                decoration: decoration,
                "{task}"
            }
        }
    )
}