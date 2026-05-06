#[derive(Debug, Clone, PartialEq)]
pub struct Todo {
    pub id: u32,
    pub task: String,
    pub is_completed: bool,
}

#[derive(Debug, Clone, Copy, PartialEq)]
pub enum TabFilter {
    All,
    Active,
    Completed,
}

impl TabFilter {
    #[allow(dead_code)]
    pub fn label(&self) -> &str {
        match self {
            TabFilter::All => "All",
            TabFilter::Active => "Active",
            TabFilter::Completed => "Completed",
        }
    }

    pub fn matches(&self, todo: &Todo) -> bool {
        match self {
            TabFilter::All => true,
            TabFilter::Active => !todo.is_completed,
            TabFilter::Completed => todo.is_completed,
        }
    }
}

pub fn default_todos() -> Vec<Todo> {
    vec![
        Todo { id: 1, task: "Task1".into(), is_completed: false },
        Todo { id: 2, task: "Task2".into(), is_completed: true },
        Todo { id: 3, task: "Task3".into(), is_completed: false },
        Todo { id: 4, task: "Task4".into(), is_completed: false },
    ]
}
