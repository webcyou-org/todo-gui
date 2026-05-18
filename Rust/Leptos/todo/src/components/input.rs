use leptos::*;
use crate::data::Todo;

#[component]
pub fn TodoInput(
    todos: RwSignal<Vec<Todo>>,
    next_id: RwSignal<u32>,
    input: RwSignal<String>,
) -> impl IntoView {
    let add_todo = move || {
        let text = input.get().trim().to_string();
        if text.is_empty() { return; }
        let id = next_id.get();
        todos.update(|v| v.push(Todo { id, task: text, is_completed: false }));
        next_id.update(|n| *n += 1);
        input.set(String::new());
    };

    view! {
        <input
            type="text"
            class="todo-input"
            placeholder="Add Task"
            prop:value=move || input.get()
            on:input=move |e| input.set(event_target_value(&e))
            on:keydown=move |e| { if e.key() == "Enter" && !e.is_composing() { add_todo(); } }
        />
    }
}