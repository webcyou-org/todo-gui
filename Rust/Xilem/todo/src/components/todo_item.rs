use xilem::masonry::properties::types::AsUnit as _;
use xilem::style::Style as _;
use xilem::view::{CrossAxisAlignment, FlexExt as _, FlexSpacer, button, flex_col, flex_row, label, portal, sized_box};
use xilem::{Color, WidgetView};

use crate::data::{AppState, Todo};
use crate::theme::{C_ACCENT, C_CB_BORDER, C_MUTED, C_SURFACE, C_TEXT};

fn todo_row(todo: &Todo) -> impl WidgetView<AppState> {
    let id = todo.id;
    let is_completed = todo.is_completed;
    let task = todo.task.clone();

    let cb_border = C_CB_BORDER;
    let cb_label = if is_completed { "✓" } else { "" };
    let cb_label_color = if is_completed { C_ACCENT } else { C_SURFACE };

    let checkbox = sized_box(
        button(
            label(cb_label).color(cb_label_color),
            move |state: &mut AppState| state.toggle(id),
        )
        .background_color(Color::TRANSPARENT)
        .border(cb_border, 2.)
        .corner_radius(8.)
        .padding(0.),
    )
    .width(16.px())
    .height(16.px());

    let task_label = label(task)
        .text_size(14.)
        .color(if is_completed { C_MUTED } else { C_TEXT });

    flex_row((
        checkbox,
        FlexSpacer::Fixed(18.px()),
        task_label.flex(1.),
    ))
    .background_color(C_SURFACE)
    .corner_radius(4.)
    .padding(10.)
}

pub fn todo_list(todos: Vec<Todo>) -> impl WidgetView<AppState> {
    let rows = todos.iter().map(todo_row).collect::<Vec<_>>();
    portal(
        flex_col(rows)
            .gap(5.px())
            .cross_axis_alignment(CrossAxisAlignment::Fill),
    )
}