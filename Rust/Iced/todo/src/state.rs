#[derive(Debug, Clone)]
pub struct TodoItem {
    pub id: usize,
    pub task: String,
    pub completed: bool,
}

#[derive(Debug, Clone, PartialEq)]
pub enum Tab {
    All,
    Active,
    Completed,
}

pub struct TodoApp {
    pub todos: Vec<TodoItem>,
    pub input: String,
    pub active_tab: Tab,
    pub next_id: usize,
}

#[derive(Debug, Clone)]
pub enum Message {
    InputChanged(String),
    AddTodo,
    ToggleTodo(usize),
    SetTab(Tab),
}

impl TodoApp {
    pub fn new() -> Self {
        TodoApp {
            todos: vec![
                TodoItem { id: 1, task: "Task 1".into(), completed: false },
                TodoItem { id: 2, task: "Task 2".into(), completed: true },
                TodoItem { id: 3, task: "Task 3".into(), completed: false },
                TodoItem { id: 4, task: "Task 4".into(), completed: false },
            ],
            input: String::new(),
            active_tab: Tab::All,
            next_id: 5,
        }
    }

    pub fn add_todo(&mut self, task: String) {
        let task = task.trim().to_string();
        if task.is_empty() { return; }
        self.todos.push(TodoItem { id: self.next_id, task, completed: false });
        self.next_id += 1;
    }

    pub fn toggle_todo(&mut self, id: usize) {
        if let Some(t) = self.todos.iter_mut().find(|t| t.id == id) {
            t.completed = !t.completed;
        }
    }

    pub fn filtered_todos(&self) -> Vec<&TodoItem> {
        self.todos.iter()
            .filter(|t| match &self.active_tab {
                Tab::All => true,
                Tab::Active => !t.completed,
                Tab::Completed => t.completed,
            })
            .collect()
    }
}