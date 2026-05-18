mod data;
mod components;

use leptos::*;
use wasm_bindgen::prelude::*;
use data::{initial_todos, TabFilter};
use components::{TodoInput, TabMenu, TodoList};

#[component]
fn App() -> impl IntoView {
    let todos = create_rw_signal(initial_todos());
    let active_tab = create_rw_signal(TabFilter::All);
    let next_id = create_rw_signal(5u32);
    let input = create_rw_signal(String::new());

    view! {
        <div class="app">
            <h1 class="title">"ToDo"</h1>
            <TodoInput todos=todos next_id=next_id input=input />
            <TabMenu active_tab=active_tab />
            <TodoList todos=todos active_tab=active_tab />
        </div>
    }
}

#[wasm_bindgen(start)]
pub fn main() {
    console_error_panic_hook::set_once();
    web_sys::console::log_1(&"[leptos-todo] main() start".into());
    mount_to_body(|| {
        web_sys::console::log_1(&"[leptos-todo] mounting App".into());
        view! { <App/> }
    });
    web_sys::console::log_1(&"[leptos-todo] mount_to_body returned".into());
}