#[derive(Clone, PartialEq, Debug)]
pub struct Todo {
    pub id: u32,
    pub task: String,
    pub is_completed: bool,
}

#[derive(Clone, Copy, PartialEq, Debug)]
pub enum TabFilter {
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

pub fn initial_todos() -> Vec<Todo> {
    vec![
        Todo { id: 1, task: "Task1".into(), is_completed: false },
        Todo { id: 2, task: "Task2".into(), is_completed: true },
        Todo { id: 3, task: "Task3".into(), is_completed: false },
        Todo { id: 4, task: "Task4".into(), is_completed: false },
    ]
}