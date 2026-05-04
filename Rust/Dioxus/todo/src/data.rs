#[derive(Clone, PartialEq)]
pub struct Todo {
    pub id: u64,
    pub task: String,
    pub is_completed: bool,
}

impl Todo {
    pub fn new(id: u64, task: impl Into<String>) -> Self {
        Self { id, task: task.into(), is_completed: false }
    }

    pub fn initial_todos() -> Vec<Todo> {
        vec![
            Todo::new(1, "Task 1"),
            Todo { id: 2, task: "Task 2".into(), is_completed: true },
            Todo::new(3, "Task 3"),
            Todo::new(4, "Task 4"),
        ]
    }
}

#[derive(Clone, PartialEq)]
pub enum TabFilter {
    All,
    Active,
    Completed,
}

impl TabFilter {
    pub fn label(&self) -> &'static str {
        match self {
            TabFilter::All       => "All",
            TabFilter::Active    => "Active",
            TabFilter::Completed => "Completed",
        }
    }

    pub fn matches(&self, todo: &Todo) -> bool {
        match self {
            TabFilter::All       => true,
            TabFilter::Active    => !todo.is_completed,
            TabFilter::Completed => todo.is_completed,
        }
    }
}