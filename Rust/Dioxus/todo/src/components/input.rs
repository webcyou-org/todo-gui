use dioxus::prelude::*;
use crate::data::Todo;

#[component]
pub fn TodoInput(
    mut input: Signal<String>,
    mut todos: Signal<Vec<Todo>>,
    mut next_id: Signal<u64>,
) -> Element {
    let mut add_todo = move || {
        let task = input.read().trim().to_string();
        if !task.is_empty() {
            todos.write().push(Todo::new(*next_id.read(), task));
            *next_id.write() += 1;
            input.set(String::new());
        }
    };

    rsx! {
        div {
            style: "margin-bottom: 14px;",
            input {
                class: "todo-input",
                r#type: "text",
                placeholder: "Add Task",
                value: "{input}",
                oninput: move |e| input.set(e.value()),
                onkeydown: move |e| {
                    if e.key() == Key::Enter { add_todo(); }
                },
            }
        }
    }
}