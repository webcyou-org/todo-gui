use makepad_widgets::*;
use crate::data::*;
use std::collections::HashMap;

#[derive(Clone, Debug, DefaultNone)]
pub enum TodoListAction {
    Toggle(usize),
    None,
}

live_design! {
    link widgets;
    use link::widgets::*;
    use link::theme::*;

    C_SURFACE   = #2A2A2A;
    C_TEXT      = #D2D2D2;
    C_MUTED     = #9B9B9B;
    C_ACCENT    = #5DC2AF;
    C_CB_BORDER = #D9D9D9;

    TodoItemTemplate = <RoundedView> {
        width: Fill,
        height: 35.0,
        margin: { bottom: 5.0 },
        padding: { top: 10.0, left: 10.0, right: 10.0, bottom: 10.0 },
        flow: Right,
        align: { y: 0.5 },
        show_bg: true,
        draw_bg: {
            color: (C_SURFACE),
            border_radius: 4.0,
        },

        check = <CheckBox> {
            width: 16.0,
            height: 16.0,
            margin: { right: 18.0 },
            draw_bg: {
                size: 16.0,
                border_radius: 8.0,
                border_size: 2.0,
                color: (C_SURFACE),
                color_active: (C_ACCENT),
                border_color_1: (C_CB_BORDER),
                border_color_2: (C_CB_BORDER),
                border_color_1_active: (C_ACCENT),
                border_color_2_active: (C_ACCENT),
                mark_color: #0000,
                mark_color_active: #FFFFFF,
            }
        }

        label = <Label> {
            width: Fill,
            draw_text: {
                color: (C_TEXT),
                text_style: { font_size: 14.0 },
            }
        }
    }

    pub TodoListBase = {{TodoList}} {}
    pub TodoList = <TodoListBase> {
        width: Fill,
        height: Fill,
        list: <PortalList> {
            TodoItemTemplate = <TodoItemTemplate> {}
        }
    }
}

#[derive(Live, LiveHook, Widget)]
pub struct TodoList {
    #[walk] walk: Walk,
    #[layout] layout: Layout,
    #[redraw] #[live] list: PortalList,
    #[rust] items: Vec<Todo>,
    #[rust] item_uid_map: HashMap<WidgetUid, usize>,
}

impl Widget for TodoList {
    fn handle_event(&mut self, cx: &mut Cx, event: &Event, scope: &mut Scope) {
        self.list.handle_event(cx, event, scope);

        if let Event::Actions(actions) = event {
            let list_uid = self.list.widget_uid();
            for action in actions.iter() {
                if let Some(wa) = action.as_widget_action() {
                    if let Some(group) = &wa.group {
                        if group.group_uid == list_uid {
                            if let CheckBoxAction::Change(_) = wa.cast::<CheckBoxAction>() {
                                if let Some(&entry_id) = self.item_uid_map.get(&group.item_uid) {
                                    if let Some(todo) = self.items.get(entry_id) {
                                        let todo_id = todo.id;
                                        cx.widget_action(
                                            self.widget_uid(),
                                            &scope.path,
                                            TodoListAction::Toggle(todo_id),
                                        );
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    fn draw_walk(&mut self, cx: &mut Cx2d, scope: &mut Scope, walk: Walk) -> DrawStep {
        if self.list.draw_walk(cx, scope, walk).is_step() {
            self.list.set_item_range(cx, 0, self.items.len());
            while let Some(index) = self.list.next_visible_item(cx) {
                if index >= self.items.len() {
                    break;
                }
                let todo = self.items[index].clone();
                let item = self.list.item(cx, index, live_id!(TodoItemTemplate));

                self.item_uid_map.insert(item.widget_uid(), index);
                item.check_box(id!(check)).set_active(cx, todo.is_completed);
                item.label(id!(label)).set_text(cx, &todo.task);
                let label_color = if todo.is_completed {
                    Vec4 { x: 0.60784, y: 0.60784, z: 0.60784, w: 1.0 }
                } else {
                    Vec4 { x: 0.82353, y: 0.82353, z: 0.82353, w: 1.0 }
                };
                item.label(id!(label)).apply_over(cx, live! { draw_text: { color: (label_color) } });

                item.draw_all(cx, scope);
            }
            let _ = self.list.draw_walk(cx, scope, walk);
        }
        DrawStep::done()
    }
}

impl TodoListRef {
    pub fn set_items(&self, cx: &mut Cx, items: Vec<Todo>) {
        if let Some(mut inner) = self.borrow_mut() {
            inner.items = items;
            inner.redraw(cx);
        }
    }

    pub fn toggle_action(&self, actions: &Actions) -> Option<usize> {
        for action in actions.filter_widget_actions_cast::<TodoListAction>(self.widget_uid()) {
            if let TodoListAction::Toggle(id) = action {
                return Some(id);
            }
        }
        None
    }
}