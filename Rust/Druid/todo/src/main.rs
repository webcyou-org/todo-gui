use druid::im::Vector;
use druid::{AppLauncher, Data, Lens, Widget, WindowDesc};
use druid::widget::Label;

// ---------------------------------------------------------------------------
// Data Model
// ---------------------------------------------------------------------------

#[derive(Clone, Data, Lens, PartialEq)]
struct Todo {
    id: u64,
    task: String,
    is_completed: bool,
}

impl Todo {
    fn new(id: u64, task: impl Into<String>) -> Self {
        Self { id, task: task.into(), is_completed: false }
    }
}

#[derive(Clone, Data, PartialEq)]
enum TabFilter {
    All,
    Active,
    Completed,
}

impl TabFilter {
    fn label(&self) -> &str {
        match self {
            TabFilter::All => "All",
            TabFilter::Active => "Active",
            TabFilter::Completed => "Completed",
        }
    }

    fn matches(&self, todo: &Todo) -> bool {
        match self {
            TabFilter::All => true,
            TabFilter::Active => !todo.is_completed,
            TabFilter::Completed => todo.is_completed,
        }
    }
}

#[derive(Clone, Data, Lens)]
struct AppState {
    todos: Vector<Todo>,
    input: String,
    active_tab: TabFilter,
    next_id: u64,
}

impl AppState {
    fn new() -> Self {
        let todos = Vector::from(vec![
            Todo::new(1, "Task 1"),
            { let mut t = Todo::new(2, "Task 2"); t.is_completed = true; t },
            Todo::new(3, "Task 3"),
            Todo::new(4, "Task 4"),
        ]);
        Self {
            todos,
            input: String::new(),
            active_tab: TabFilter::All,
            next_id: 5,
        }
    }

    fn add_todo(&mut self) {
        let task = self.input.trim().to_string();
        if !task.is_empty() {
            self.todos.push_back(Todo::new(self.next_id, task));
            self.next_id += 1;
            self.input.clear();
        }
    }

    fn toggle_completed(&mut self, id: u64) {
        for todo in self.todos.iter_mut() {
            if todo.id == id {
                todo.is_completed = !todo.is_completed;
                break;
            }
        }
    }

    fn filtered_todos(&self) -> Vector<Todo> {
        self.todos
            .iter()
            .filter(|t| self.active_tab.matches(t))
            .cloned()
            .collect()
    }
}

// ---------------------------------------------------------------------------
// UI (placeholder — will be built in next steps)
// ---------------------------------------------------------------------------

fn build_ui() -> impl Widget<AppState> {
    Label::new("Step 1 complete — data model ready")
}

fn main() {
    let main_window = WindowDesc::new(build_ui())
        .window_size((800.0, 600.0))
        .title("ToDo");

    AppLauncher::with_window(main_window)
        .launch(AppState::new())
        .expect("Failed to launch application");
}