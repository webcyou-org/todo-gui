// Data model: Todo, TabFilter, initial data

#[derive(Clone, PartialEq)]
pub struct Todo {
    pub id: usize,
    pub task: String,
    pub is_completed: bool,
}

#[derive(Clone, PartialEq, Copy, Debug)]
pub enum TabFilter {
    All,
    Active,
    Completed,
}

impl TabFilter {
    pub fn label(&self) -> &'static str {
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
        Todo { id: 1, task: "Task 1".to_string(), is_completed: false },
        Todo { id: 2, task: "Task 2".to_string(), is_completed: true },
        Todo { id: 3, task: "Task 3".to_string(), is_completed: false },
        Todo { id: 4, task: "Task 4".to_string(), is_completed: false },
    ]
}