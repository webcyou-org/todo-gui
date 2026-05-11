use vizia::prelude::*;

#[derive(Lens, Clone, PartialEq, Debug)]
pub struct Todo {
    pub id: usize,
    pub task: String,
    pub is_completed: bool,
}

impl Data for Todo {
    fn same(&self, other: &Self) -> bool {
        self == other
    }
}

#[derive(Lens, Clone, PartialEq, Debug)]
pub struct AppData {
    pub todos: Vec<Todo>,
    pub filtered_todos: Vec<Todo>,
    pub active_tab: usize,
    pub input_text: String,
    pub next_id: usize,
}

impl AppData {
    pub fn new() -> Self {
        let todos = vec![
            Todo { id: 1, task: "Task 1".to_string(), is_completed: false },
            Todo { id: 2, task: "Task 2".to_string(), is_completed: true },
            Todo { id: 3, task: "Task 3".to_string(), is_completed: false },
            Todo { id: 4, task: "Task 4".to_string(), is_completed: false },
        ];
        let filtered_todos = todos.clone();
        AppData {
            todos,
            filtered_todos,
            active_tab: 0,
            input_text: String::new(),
            next_id: 5,
        }
    }

    pub fn recompute_filtered(&mut self) {
        self.filtered_todos = self.todos.iter()
            .filter(|t| match self.active_tab {
                1 => !t.is_completed,
                2 => t.is_completed,
                _ => true,
            })
            .cloned()
            .collect();
    }
}

#[derive(Debug)]
pub enum AppEvent {
    AddTodo,
    ToggleTodo(usize),
    SetActiveTab(usize),
    SetInputText(String),
}

impl Model for AppData {
    fn event(&mut self, _cx: &mut EventContext, event: &mut Event) {
        event.map(|app_event, _| match app_event {
            AppEvent::AddTodo => {
                let task = self.input_text.trim().to_string();
                if !task.is_empty() {
                    self.todos.push(Todo {
                        id: self.next_id,
                        task,
                        is_completed: false,
                    });
                    self.next_id += 1;
                    self.input_text = String::new();
                    self.recompute_filtered();
                }
            }
            AppEvent::ToggleTodo(id) => {
                let id = *id;
                if let Some(todo) = self.todos.iter_mut().find(|t| t.id == id) {
                    todo.is_completed = !todo.is_completed;
                }
                self.recompute_filtered();
            }
            AppEvent::SetActiveTab(tab) => {
                self.active_tab = *tab;
                self.recompute_filtered();
            }
            AppEvent::SetInputText(text) => {
                self.input_text = text.clone();
            }
        });
    }
}