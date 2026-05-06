mod data;
mod theme;

use data::{default_todos, TabFilter, Todo};
use theme::*;

use rui::*;

#[derive(Clone)]
struct AppState {
    todos: Vec<Todo>,
    active_tab: TabFilter,
    next_id: u32,
}

impl AppState {
    fn new() -> Self {
        let todos = default_todos();
        let next_id = todos.iter().map(|t| t.id).max().unwrap_or(0) + 1;
        Self {
            todos,
            active_tab: TabFilter::All,
            next_id,
        }
    }

    fn filtered_todos(&self) -> Vec<Todo> {
        self.todos
            .iter()
            .filter(|t| self.active_tab.matches(t))
            .cloned()
            .collect()
    }

    fn toggle_todo(&mut self, id: u32) {
        if let Some(todo) = self.todos.iter_mut().find(|t| t.id == id) {
            todo.is_completed = !todo.is_completed;
        }
    }
}

fn checkbox_view(is_completed: bool) -> impl View {
    canvas(move |_, rect, vger| {
        let size = 16.0;
        let cx = rect.origin.x + (rect.size.width - size) / 2.0;
        let cy = rect.origin.y + (rect.size.height - size) / 2.0;
        let center: LocalPoint = [cx + size / 2.0, cy + size / 2.0].into();

        if is_completed {
            let paint = vger.color_paint(C_ACCENT);
            vger.fill_circle(center, size / 2.0, paint);
        } else {
            let paint = vger.color_paint(C_CB_BORDER);
            vger.stroke_arc(center, size / 2.0, 2.0, 0.0, std::f32::consts::TAU, paint);
        }
    })
    .size([34.0, 35.0])
}

fn main() {
    rui(state(AppState::new, |app, cx| {
        let filtered = cx[app].filtered_todos();

        vstack((
            text("ToDo")
                .font_size(18)
                .color(C_WHITE),
            state(
                || String::new(),
                move |input, _| {
                    hstack((
                        text_editor(input)
                            .padding(Auto),
                        button("Add", move |cx| {
                            let txt = cx[input].trim().to_string();
                            if !txt.is_empty() {
                                let id = cx[app].next_id;
                                cx[app].next_id += 1;
                                cx[app].todos.push(Todo {
                                    id,
                                    task: txt,
                                    is_completed: false,
                                });
                                cx[input].clear();
                            }
                        }),
                    ))
                    .background(
                        rectangle()
                            .corner_radius(4.0)
                            .color(C_INPUT),
                    )
                    .size([0.0, 35.0])
                },
            ),
            hstack((
                button("All", move |cx| {
                    cx[app].active_tab = TabFilter::All;
                }),
                button("Active", move |cx| {
                    cx[app].active_tab = TabFilter::Active;
                }),
                button("Completed", move |cx| {
                    cx[app].active_tab = TabFilter::Completed;
                }),
            )),
            list(
                filtered.iter().map(|t| t.id as usize).collect(),
                move |idx| {
                    let todo_id = *idx as u32;
                    with_ref(app, move |state| {
                        let todo = state
                            .filtered_todos()
                            .into_iter()
                            .find(|t| t.id == todo_id)
                            .unwrap_or(Todo {
                                id: 0,
                                task: String::new(),
                                is_completed: false,
                            });
                        let id = todo.id;
                        let task = todo.task.clone();
                        let is_completed = todo.is_completed;
                        let text_color = if is_completed { C_MUTED } else { C_TEXT };

                        hstack((
                            checkbox_view(is_completed)
                                .tap(move |cx| {
                                    cx[app].toggle_todo(id);
                                }),
                            text(&task)
                                .font_size(14)
                                .color(text_color),
                            spacer(),
                        ))
                        .background(
                            rectangle()
                                .corner_radius(4.0)
                                .color(C_SURFACE),
                        )
                        .size([0.0, 35.0])
                    })
                },
            ),
        ))
        .padding(10.0)
        .background(rectangle().color(C_BG))
    })
    .window_title("ToDo")
    .size([800.0, 600.0]));
}
