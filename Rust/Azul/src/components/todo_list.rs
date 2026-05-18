use azul::prelude::*;
use azul::callbacks::CallbackType;
use crate::data::{AppState, Todo, ToggleData};
use crate::theme::*;

extern "C" fn on_toggle(mut data: RefAny, _: CallbackInfo) -> Update {
    let (id, mut app_ref) = {
        let d = match data.downcast_ref::<ToggleData>() {
            Some(d) => d,
            None => return Update::DoNothing,
        };
        (d.id, d.app.clone())
    };
    if let Some(mut app) = app_ref.downcast_mut::<AppState>() {
        app.toggle_todo(id);
    }
    Update::RefreshDom
}

fn build_checkbox(is_completed: bool, toggle_data: RefAny) -> Dom {
    let bg = if is_completed { C_ACCENT } else { "transparent" };
    let border = if is_completed { C_ACCENT } else { C_CB_BORDER };
    let style = format!(
        "width: 16px; height: 16px; min-width: 16px; min-height: 16px; \
         border-radius: 8px; border-width: 2px; border-style: solid; \
         border-color: {border}; background-color: {bg}; \
         margin-right: 18px;"
    );
    let mut div = Dom::create_div().with_inline_style(style.as_str());
    div.add_callback(
        EventFilter::Hover(HoverEventFilter::LeftMouseUp),
        toggle_data,
        on_toggle as CallbackType,
    );
    div
}

fn build_todo_item(todo: &Todo, app_data: RefAny) -> Dom {
    let toggle_data = RefAny::new(ToggleData { app: app_data, id: todo.id });

    let (text_color, decoration) = if todo.is_completed {
        (C_MUTED, "line-through")
    } else {
        (C_TEXT, "none")
    };
    let label_style = format!(
        "color: {text_color}; font-size: 14px; text-decoration-line: {decoration}; flex-grow: 1;"
    );

    let checkbox_dom = build_checkbox(todo.is_completed, toggle_data);
    let label = Dom::create_text(todo.task.as_str())
        .with_inline_style(label_style.as_str());

    let item_style = format!(
        "background-color: {C_SURFACE}; height: 35px; border-radius: 4px; \
         padding-top: 0px; padding-bottom: 0px; padding-left: 10px; padding-right: 10px; \
         margin-bottom: 5px; flex-direction: row; align-items: center; width: 100%;"
    );
    Dom::create_div()
        .with_inline_style(item_style.as_str())
        .with_child(checkbox_dom)
        .with_child(label)
}

pub fn build_todo_list(state: &AppState, data: RefAny) -> Dom {
    let items: Vec<Dom> = state.filtered_todos().iter()
        .map(|t| build_todo_item(t, data.clone()))
        .collect();

    let mut list = Dom::create_div()
        .with_inline_style("flex-direction: column; flex-grow: 1; overflow: scroll;");
    for item in items {
        list.add_child(item);
    }
    list
}