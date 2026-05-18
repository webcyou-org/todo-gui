use azul::prelude::RefAny;

#[derive(Clone, Debug, PartialEq)]
pub enum TabFilter {
    All,
    Active,
    Completed,
}

#[derive(Clone, Debug)]
pub struct Todo {
    pub id: usize,
    pub task: String,
    pub is_completed: bool,
}

#[derive(Clone, Debug)]
pub struct AppState {
    pub todos: Vec<Todo>,
    pub input_text: String,
    pub active_tab: TabFilter,
    pub next_id: usize,
}

impl AppState {
    pub fn new() -> Self {
        let todos = vec![
            Todo { id: 1, task: "Task 1".into(), is_completed: false },
            Todo { id: 2, task: "Task 2".into(), is_completed: true },
            Todo { id: 3, task: "Task 3".into(), is_completed: false },
            Todo { id: 4, task: "Task 4".into(), is_completed: false },
        ];
        AppState { todos, input_text: String::new(), active_tab: TabFilter::All, next_id: 5 }
    }

    pub fn add_todo(&mut self, task: String) {
        if task.trim().is_empty() { return; }
        self.todos.push(Todo { id: self.next_id, task, is_completed: false });
        self.next_id += 1;
    }

    pub fn toggle_todo(&mut self, id: usize) {
        if let Some(t) = self.todos.iter_mut().find(|t| t.id == id) {
            t.is_completed = !t.is_completed;
        }
    }

    pub fn filtered_todos(&self) -> Vec<Todo> {
        self.todos.iter().filter(|t| match self.active_tab {
            TabFilter::All => true,
            TabFilter::Active => !t.is_completed,
            TabFilter::Completed => t.is_completed,
        }).cloned().collect()
    }
}

#[derive(Clone, Debug)]
pub struct ToggleData {
    pub app: RefAny,
    pub id: usize,
}