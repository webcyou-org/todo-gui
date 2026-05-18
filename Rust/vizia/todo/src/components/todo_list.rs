use vizia::prelude::*;
use crate::data::{AppData, AppEvent};

pub fn build_todo_list(cx: &mut Context) {
    ScrollView::new(cx, 0.0, 0.0, false, true, |cx| {
        VStack::new(cx, |cx| {
            List::new(cx, AppData::filtered_todos, |cx, _idx, item| {
                Binding::new(cx, item, |cx, todo_lens| {
                    let todo = todo_lens.get(cx).clone();
                    let id = todo.id;
                    let is_completed = todo.is_completed;

                    HStack::new(cx, |cx| {
                        Label::new(cx, if is_completed { "✓" } else { "" })
                            .class("checkbox")
                            .toggle_class("checked", is_completed)
                            .on_press(move |cx| cx.emit(AppEvent::ToggleTodo(id)));

                        Label::new(cx, &todo.task)
                            .class("todo-item-text")
                            .toggle_class("completed", is_completed);
                    })
                    .class("todo-item");
                });
            });
        })
        .class("todo-list")
        .width(Stretch(1.0));
    })
    .width(Stretch(1.0))
    .height(Stretch(1.0))
    .background_color(Color::rgb(0x1C, 0x1C, 0x1C));
}