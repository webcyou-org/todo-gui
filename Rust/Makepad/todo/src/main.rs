use makepad_widgets::*;

mod data;
use data::*;

mod components;
use components::*;

live_design! {
    link widgets;
    use link::widgets::*;
    use link::theme::*;
    use crate::components::todo_list::TodoList;

    // ─── Design Tokens ───────────────────────────────────
    C_BG      = #1C1C1C;
    C_SURFACE = #2A2A2A;
    C_INPUT   = #303030;
    C_TEXT    = #D2D2D2;
    C_WHITE   = #FFFFFF;
    C_MUTED   = #9B9B9B;
    C_ACCENT  = #5DC2AF;
    C_CB_BORDER = #D9D9D9;

    App = {{App}} {
        ui: <Window> {
            window: { inner_size: vec2(800, 600) },
            pass: { clear_color: (C_BG) },
            body = <View> {
                flow: Down,
                padding: { top: 10.0, left: 24.0, right: 24.0, bottom: 10.0 },
                show_bg: true,
                draw_bg: { color: (C_BG) },

                // Title
                title_label = <Label> {
                    text: "ToDo",
                    margin: { bottom: 14.0 },
                    draw_text: {
                        color: (C_WHITE),
                        text_style: {
                            font_size: 18.0,
                        }
                    }
                }

                task_input = <TextInput> {
                    width: Fill,
                    height: 35.0,
                    margin: { bottom: 14.0 },
                    padding: { top: 4.0, bottom: 4.0, left: 16.0, right: 16.0 },
                    empty_text: "Add Task",
                    draw_bg: {
                        color: (C_INPUT),
                        border_radius: 4.0,
                        border_size: 1.0,
                        border_color_1: #0000,
                        border_color_2: #0000,
                        border_color_1_focus: (C_ACCENT),
                        border_color_2_focus: (C_ACCENT),
                    },
                    draw_text: {
                        color: (C_WHITE),
                        color_empty: (C_MUTED),
                    }
                }

                tab_row = <View> {
                    flow: Right,
                    margin: { bottom: 3.0 },
                    height: Fit,

                    tab_all = <Button> {
                        text: "All",
                        height: 28.0,
                        padding: { left: 8.0, right: 8.0, top: 0.0, bottom: 0.0 },
                        draw_bg: {
                            color: #0000,
                            color_hover: #0000,
                            color_down: #0000,
                            color_focus: #0000,
                            border_size: 0.0,
                        },
                        draw_text: {
                            color: (C_WHITE),
                            color_hover: (C_TEXT),
                            color_down: (C_TEXT),
                            text_style: { font_size: 14.0 }
                        }
                    }

                    tab_active = <Button> {
                        text: "Active",
                        height: 28.0,
                        padding: { left: 8.0, right: 8.0, top: 0.0, bottom: 0.0 },
                        draw_bg: {
                            color: #0000,
                            color_hover: #0000,
                            color_down: #0000,
                            color_focus: #0000,
                            border_size: 0.0,
                        },
                        draw_text: {
                            color: (C_TEXT),
                            color_hover: (C_TEXT),
                            color_down: (C_TEXT),
                            text_style: { font_size: 14.0 }
                        }
                    }

                    tab_completed = <Button> {
                        text: "Completed",
                        height: 28.0,
                        padding: { left: 8.0, right: 8.0, top: 0.0, bottom: 0.0 },
                        draw_bg: {
                            color: #0000,
                            color_hover: #0000,
                            color_down: #0000,
                            color_focus: #0000,
                            border_size: 0.0,
                        },
                        draw_text: {
                            color: (C_TEXT),
                            color_hover: (C_TEXT),
                            color_down: (C_TEXT),
                            text_style: { font_size: 14.0 }
                        }
                    }
                }

                todo_list = <TodoList> {}
            }
        }
    }
}

app_main!(App);

fn main() {
    app_main();
}

#[derive(Live, LiveHook)]
pub struct App {
    #[live]
    ui: WidgetRef,
    #[rust]
    data: AppData,
    #[rust]
    filtered: Vec<Todo>,
}

impl LiveRegister for App {
    fn live_register(cx: &mut Cx) {
        makepad_widgets::live_design(cx);
        crate::components::todo_list::live_design(cx);
    }
}

impl AppMain for App {
    fn handle_event(&mut self, cx: &mut Cx, event: &Event) {
        self.match_event(cx, event);
        let scope = &mut Scope::empty();
        self.ui.handle_event(cx, event, scope);
    }
}

impl App {
    fn update_tab_visuals(&self, cx: &mut Cx) {
        let tabs = [
            (id!(tab_all), TabFilter::All),
            (id!(tab_active), TabFilter::Active),
            (id!(tab_completed), TabFilter::Completed),
        ];
        for (tab_id, filter) in &tabs {
            let color = if *filter == self.data.active_tab {
                live! { draw_text: { color: #FFFFFF } }
            } else {
                live! { draw_text: { color: #D2D2D2 } }
            };
            self.ui.button(*tab_id).apply_over(cx, color);
        }
    }
}

impl MatchEvent for App {
    fn handle_startup(&mut self, cx: &mut Cx) {
        self.data = AppData::new();
        self.filtered = self.data.filtered();
        self.update_tab_visuals(cx);
        self.ui.todo_list(id!(todo_list)).set_items(cx, self.filtered.clone());
    }

    fn handle_actions(&mut self, cx: &mut Cx, actions: &Actions) {
        let ti = self.ui.text_input(id!(task_input));
        if let Some((text, _)) = ti.returned(actions) {
            self.data.add_todo(text);
            self.filtered = self.data.filtered();
            ti.set_text(cx, "");
            self.ui.todo_list(id!(todo_list)).set_items(cx, self.filtered.clone());
        }

        let tabs = [
            (id!(tab_all), TabFilter::All),
            (id!(tab_active), TabFilter::Active),
            (id!(tab_completed), TabFilter::Completed),
        ];
        let mut tab_changed = false;
        for (tab_id, filter) in &tabs {
            if self.ui.button(*tab_id).clicked(actions) {
                self.data.active_tab = *filter;
                self.filtered = self.data.filtered();
                tab_changed = true;
                break;
            }
        }
        if tab_changed {
            self.update_tab_visuals(cx);
            self.ui.todo_list(id!(todo_list)).set_items(cx, self.filtered.clone());
        }

        if let Some(todo_id) = self.ui.todo_list(id!(todo_list)).toggle_action(actions) {
            self.data.toggle(todo_id);
            self.filtered = self.data.filtered();
            self.ui.todo_list(id!(todo_list)).set_items(cx, self.filtered.clone());
        }
    }
}