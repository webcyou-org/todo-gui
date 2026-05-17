#[derive(Clone, Debug, PartialEq)]
pub struct Todo {
    pub id: usize,
    pub task: String,
    pub is_completed: bool,
}

#[derive(Clone, Copy, Debug, PartialEq, Default)]
pub enum TabFilter {
    #[default]
    All,
    Active,
    Completed,
}

impl TabFilter {
    pub fn label(self) -> &'static str {
        match self {
            Self::All => "All",
            Self::Active => "Active",
            Self::Completed => "Completed",
        }
    }

    pub fn matches(self, todo: &Todo) -> bool {
        match self {
            Self::All => true,
            Self::Active => !todo.is_completed,
            Self::Completed => todo.is_completed,
        }
    }
}

#[derive(Default)]
pub struct AppData {
    pub todos: Vec<Todo>,
    pub next_id: usize,
    pub active_tab: TabFilter,
}

impl AppData {
    pub fn new() -> Self {
        Self {
            todos: vec![
                Todo { id: 1, task: "Task 1".into(), is_completed: false },
                Todo { id: 2, task: "Task 2".into(), is_completed: true },
                Todo { id: 3, task: "Task 3".into(), is_completed: false },
                Todo { id: 4, task: "Task 4".into(), is_completed: false },
            ],
            next_id: 5,
            active_tab: TabFilter::default(),
        }
    }

    pub fn add_todo(&mut self, task: String) {
        if task.is_empty() {
            return;
        }
        self.todos.push(Todo { id: self.next_id, task, is_completed: false });
        self.next_id += 1;
    }

    pub fn toggle(&mut self, id: usize) {
        if let Some(t) = self.todos.iter_mut().find(|t| t.id == id) {
            t.is_completed = !t.is_completed;
        }
    }

    pub fn filtered(&self) -> Vec<Todo> {
        self.todos.iter().filter(|t| self.active_tab.matches(t)).cloned().collect()
    }
}