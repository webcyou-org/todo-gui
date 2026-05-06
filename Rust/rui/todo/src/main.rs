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

fn checkbox_canvas(is_completed: bool) -> impl View {
    let accent = c_accent();
    let border = c_cb_border();
    let bg = c_surface();

    canvas(move |_, rect, vger| {
        let size = 16.0;
        let cx = rect.origin.x + (rect.size.width - size) / 2.0;
        let cy = rect.origin.y + (rect.size.height - size) / 2.0;
        let center: LocalPoint = [cx + size / 2.0, cy + size / 2.0].into();

        if is_completed {
            let paint = vger.color_paint(accent);
            vger.fill_circle(center, size / 2.0, paint);
        } else {
            let border_paint = vger.color_paint(border);
            vger.fill_circle(center, size / 2.0, border_paint);
            let bg_paint = vger.color_paint(bg);
            vger.fill_circle(center, size / 2.0 - 1.5, bg_paint);
        }
    })
    .size([34.0, 35.0])
}

fn main() {
    rui(state(AppState::new, |app, cx| {
        let filtered = cx[app].filtered_todos();
        let bg = c_bg();
        let input_bg = c_input();
        let surface = c_surface();
        let white = c_white();
        let text_c = c_text();
        let muted = c_muted();

        zstack((
            rectangle().color(bg),
            vstack((
                hstack((
                    text("ToDo")
                        .font_size(18)
                        .color(white),
                    spacer(),
                )),
                state(
                    || String::new(),
                    move |input, _| {
                        hstack((
                            text_editor(input).flex(),
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
                                .color(input_bg),
                        )
                        .size([752.0, 35.0])
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
                    spacer(),
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
                            let text_color = if is_completed { muted } else { text_c };

                            hstack((
                                checkbox_canvas(is_completed)
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
                                    .color(surface),
                            )
                        })
                    },
                )
                .flex(),
                spacer(),
            ))
            .padding(24.0),
        ))
    })
    .window_title("ToDo")
    .size([800.0, 600.0]));
}
