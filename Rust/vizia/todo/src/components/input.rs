use vizia::prelude::*;
use crate::data::{AppData, AppEvent};

pub fn build_input(cx: &mut Context) {
    Binding::new(cx, AppData::input_version, |cx, _| {
        Textbox::new(cx, AppData::input_text)
            .class("todo-input")
            .placeholder("Add Task")
            .on_edit(|cx, text| cx.emit(AppEvent::SetInputText(text)))
            .on_submit(|cx, _text, enter| {
                if enter {
                    cx.emit(AppEvent::AddTodo);
                }
            });
    });
}