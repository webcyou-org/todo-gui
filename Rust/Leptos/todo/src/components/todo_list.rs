use leptos::*;
use crate::data::{Todo, TabFilter};

#[component]
pub fn TodoList(
    todos: RwSignal<Vec<Todo>>,
    active_tab: RwSignal<TabFilter>,
) -> impl IntoView {
    let toggle = move |id: u32| {
        todos.update(|v| {
            if let Some(t) = v.iter_mut().find(|t| t.id == id) {
                t.is_completed = !t.is_completed;
            }
        });
    };

    let filtered = create_memo(move |_| {
        let tab = active_tab.get();
        todos.get().into_iter().filter(|t| tab.matches(t)).collect::<Vec<_>>()
    });

    view! {
        <div class="todo-list">
            <For
                each=move || filtered.get()
                key=|todo| todo.id
                children=move |todo| {
                    let id = todo.id;
                    let task = todo.task.clone();
                    let done = create_memo(move |_| {
                        todos.get().iter().find(|t| t.id == id).map(|t| t.is_completed).unwrap_or(false)
                    });
                    view! {
                        <div class="todo-item">
                            <div
                                class=move || if done.get() { "checkbox checked" } else { "checkbox" }
                                on:click=move |_| toggle(id)
                            />
                            <span class=move || if done.get() { "todo-text completed" } else { "todo-text" }>
                                {task}
                            </span>
                        </div>
                    }
                }
            />
        </div>
    }
}