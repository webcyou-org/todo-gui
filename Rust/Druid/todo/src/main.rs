mod data;
mod lens;
mod theme;
mod widget;

use druid::widget::{CrossAxisAlignment, Flex, Label, List, Padding, Scroll};
use druid::{AppLauncher, FontDescriptor, FontFamily, FontWeight, Widget, WidgetExt, WindowDesc};

use data::AppState;
use lens::FilteredLens;
use theme::{BG, TEXT_WHITE};
use widget::{build_input, build_tabs, make_todo_row};

fn build_ui() -> impl Widget<AppState> {
    let title_font = FontDescriptor::new(FontFamily::SYSTEM_UI)
        .with_weight(FontWeight::BOLD)
        .with_size(18.0);

    let title = Label::new("ToDo")
        .with_font(title_font)
        .with_text_color(TEXT_WHITE);

    let todo_list = Scroll::new(
        List::new(|| make_todo_row()).lens(FilteredLens),
    )
    .vertical()
    .expand_width();

    let column = Flex::column()
        .cross_axis_alignment(CrossAxisAlignment::Start)
        .with_child(title)
        .with_spacer(14.0)
        .with_child(build_input())
        .with_spacer(14.0)
        .with_child(build_tabs())
        .with_spacer(3.0)
        .with_flex_child(todo_list, 1.0);

    Padding::new((24.0, 10.0), column)
        .background(BG)
        .expand()
}

fn main() {
    let main_window = WindowDesc::new(build_ui())
        .window_size((800.0, 600.0))
        .title("ToDo");

    AppLauncher::with_window(main_window)
        .launch(AppState::new())
        .expect("Failed to launch application");
}