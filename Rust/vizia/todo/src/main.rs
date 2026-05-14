mod data;
mod theme;
mod components;

use vizia::prelude::*;
use data::AppData;
use theme::STYLE;
use components::{input::build_input, tabs::build_tabs, todo_list::build_todo_list};

fn main() -> Result<(), ApplicationError> {
    Application::new(|cx| {
        cx.add_stylesheet(STYLE).expect("Failed to add stylesheet");
        AppData::new().build(cx);

        VStack::new(cx, |cx| {
            Label::new(cx, "ToDo").class("title");
            build_input(cx);
            build_tabs(cx);
            build_todo_list(cx);
        })
        .background_color(Color::rgb(0x1C, 0x1C, 0x1C))
        .width(Stretch(1.0))
        .height(Stretch(1.0))
        .child_left(Pixels(24.0))
        .child_right(Pixels(24.0))
        .child_top(Pixels(10.0))
        .child_bottom(Pixels(10.0));
    })
    .title("ToDo")
    .inner_size((800, 600))
    .run()
}