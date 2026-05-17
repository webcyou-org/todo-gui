#[derive(Clone)]
pub struct Todo {
    pub id: usize,
    pub task: String,
    pub is_completed: bool,
}

#[derive(Clone, Copy, PartialEq, Eq)]
pub enum TabFilter {
    All,
    Active,
    Completed,
}

impl TabFilter {
    pub fn label(self) -> &'static str {
        match self {
            TabFilter::All => "All",
            TabFilter::Active => "Active",
            TabFilter::Completed => "Completed",
        }
    }

    pub fn matches(self, todo: &Todo) -> bool {
        match self {
            TabFilter::All => true,
            TabFilter::Active => !todo.is_completed,
            TabFilter::Completed => todo.is_completed,
        }
    }
}

pub struct AppState {
    pub todos: Vec<Todo>,
    pub input: String,
    pub active_tab: TabFilter,
    next_id: usize,
}

impl AppState {
    pub fn new() -> Self {
        Self {
            todos: vec![
                Todo { id: 1, task: "Task 1".into(), is_completed: false },
                Todo { id: 2, task: "Task 2".into(), is_completed: true },
                Todo { id: 3, task: "Task 3".into(), is_completed: false },
                Todo { id: 4, task: "Task 4".into(), is_completed: false },
            ],
            input: String::new(),
            active_tab: TabFilter::All,
            next_id: 5,
        }
    }

    pub fn add_todo(&mut self) {
        let task = self.input.trim().to_string();
        if task.is_empty() {
            return;
        }
        self.todos.push(Todo {
            id: self.next_id,
            task,
            is_completed: false,
        });
        self.next_id += 1;
        self.input.clear();
    }

    pub fn toggle(&mut self, id: usize) {
        if let Some(todo) = self.todos.iter_mut().find(|t| t.id == id) {
            todo.is_completed = !todo.is_completed;
        }
    }

    pub fn filtered_todos(&self) -> Vec<Todo> {
        self.todos
            .iter()
            .filter(|t| self.active_tab.matches(t))
            .cloned()
            .collect()
    }
}