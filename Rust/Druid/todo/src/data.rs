use druid::im::Vector;
use druid::{Data, Lens};

#[derive(Clone, Data, Lens, PartialEq)]
pub struct Todo {
    pub id: u64,
    pub task: String,
    pub is_completed: bool,
}

impl Todo {
    pub fn new(id: u64, task: impl Into<String>) -> Self {
        Self { id, task: task.into(), is_completed: false }
    }
}

#[derive(Clone, Data, PartialEq)]
pub enum TabFilter {
    All,
    Active,
    Completed,
}

impl TabFilter {
    pub fn matches(&self, todo: &Todo) -> bool {
        match self {
            TabFilter::All       => true,
            TabFilter::Active    => !todo.is_completed,
            TabFilter::Completed => todo.is_completed,
        }
    }
}

#[derive(Clone, Data, Lens)]
pub struct AppState {
    pub todos: Vector<Todo>,
    pub input: String,
    pub active_tab: TabFilter,
    pub next_id: u64,
}

impl AppState {
    pub fn new() -> Self {
        let todos = Vector::from(vec![
            Todo::new(1, "Task 1"),
            { let mut t = Todo::new(2, "Task 2"); t.is_completed = true; t },
            Todo::new(3, "Task 3"),
            Todo::new(4, "Task 4"),
        ]);
        Self { todos, input: String::new(), active_tab: TabFilter::All, next_id: 5 }
    }

    pub fn add_todo(&mut self) {
        let task = self.input.trim().to_string();
        if !task.is_empty() {
            self.todos.push_back(Todo::new(self.next_id, task));
            self.next_id += 1;
            self.input.clear();
        }
    }

    pub fn filtered_todos(&self) -> Vector<Todo> {
        self.todos.iter().filter(|t| self.active_tab.matches(t)).cloned().collect()
    }
}