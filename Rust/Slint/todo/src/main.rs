#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]

use std::cell::RefCell;
use std::rc::Rc;
use slint::{ModelRc, VecModel};

slint::include_modules!();

struct TodoData {
    id: i32,
    task: String,
    is_completed: bool,
}

struct AppState {
    todos: Vec<TodoData>,
    active_tab: i32,
    next_id: i32,
}

impl AppState {
    fn new() -> Self {
        AppState {
            todos: vec![
                TodoData { id: 1, task: "Task 1".into(), is_completed: false },
                TodoData { id: 2, task: "Task 2".into(), is_completed: true },
                TodoData { id: 3, task: "Task 3".into(), is_completed: false },
                TodoData { id: 4, task: "Task 4".into(), is_completed: false },
            ],
            active_tab: 0,
            next_id: 5,
        }
    }

    fn add_todo(&mut self, task: &str) {
        if task.trim().is_empty() { return; }
        self.todos.push(TodoData { id: self.next_id, task: task.into(), is_completed: false });
        self.next_id += 1;
    }

    fn toggle_todo(&mut self, id: i32) {
        if let Some(t) = self.todos.iter_mut().find(|t| t.id == id) {
            t.is_completed = !t.is_completed;
        }
    }

    fn filtered_items(&self) -> Vec<TodoItem> {
        self.todos.iter()
            .filter(|t| match self.active_tab {
                1 => !t.is_completed,
                2 => t.is_completed,
                _ => true,
            })
            .map(|t| TodoItem {
                id: t.id,
                task: t.task.as_str().into(),
                is_completed: t.is_completed,
            })
            .collect()
    }
}

fn sync_ui(ui: &AppWindow, state: &AppState) {
    let items = state.filtered_items();
    ui.set_todos(ModelRc::new(VecModel::from(items)));
    ui.set_active_tab(state.active_tab);
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let ui = AppWindow::new()?;
    let state = Rc::new(RefCell::new(AppState::new()));

    sync_ui(&ui, &state.borrow());

    ui.on_add_todo({
        let state = state.clone();
        let ui = ui.as_weak();
        move |task| {
            let ui = ui.unwrap();
            state.borrow_mut().add_todo(&task);
            sync_ui(&ui, &state.borrow());
        }
    });

    ui.on_toggle_todo({
        let state = state.clone();
        let ui = ui.as_weak();
        move |id| {
            let ui = ui.unwrap();
            state.borrow_mut().toggle_todo(id);
            sync_ui(&ui, &state.borrow());
        }
    });

    ui.on_set_tab({
        let state = state.clone();
        let ui = ui.as_weak();
        move |tab| {
            let ui = ui.unwrap();
            state.borrow_mut().active_tab = tab;
            sync_ui(&ui, &state.borrow());
        }
    });

    ui.run()?;
    Ok(())
}
