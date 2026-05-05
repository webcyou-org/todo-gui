#[derive(Clone, serde::Deserialize, serde::Serialize)]
pub struct Todo {
    pub id: usize,
    pub task: String,
    pub is_completed: bool,
}

#[derive(Clone, Copy, PartialEq, Default, serde::Deserialize, serde::Serialize)]
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

    pub fn all() -> [Self; 3] {
        [Self::All, Self::Active, Self::Completed]
    }
}