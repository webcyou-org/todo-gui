use xilem::masonry::properties::Padding;
use xilem::masonry::properties::types::AsUnit as _;
use xilem::style::Style as _;
use xilem::view::{sized_box, text_input};
use xilem::WidgetView;

use crate::data::AppState;
use crate::theme::{C_ACCENT, C_INPUT, C_MUTED, C_WHITE};

pub fn todo_input(state: &AppState) -> impl WidgetView<AppState> {
    sized_box(
        text_input(state.input.clone(), |state: &mut AppState, new_val| {
            state.input = new_val;
        })
        .placeholder("Add Task")
        .text_color(C_WHITE)
        .on_enter(|state: &mut AppState, _| state.add_todo())
        .placeholder_color(C_MUTED)
        .background_color(C_INPUT)
        .border(C_ACCENT, 1.)
        .corner_radius(4.)
        .padding(Padding::from_vh(4., 16.)),
    )
    .height(35.px())
}