use druid::im::Vector;
use druid::Lens;

use crate::data::{AppState, Todo};

pub struct FilteredLens;

impl Lens<AppState, Vector<Todo>> for FilteredLens {
    fn with<V, F: FnOnce(&Vector<Todo>) -> V>(&self, data: &AppState, f: F) -> V {
        f(&data.filtered_todos())
    }

    fn with_mut<V, F: FnOnce(&mut Vector<Todo>) -> V>(&self, data: &mut AppState, f: F) -> V {
        let mut filtered = data.filtered_todos();
        let result = f(&mut filtered);
        for ft in &filtered {
            if let Some(t) = data.todos.iter_mut().find(|t| t.id == ft.id) {
                *t = ft.clone();
            }
        }
        result
    }
}