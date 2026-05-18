use azul::prelude::*;
use azul::callbacks::CallbackType;
use crate::data::{AppState, TabFilter};
use crate::theme::C_TEXT;

extern "C" fn on_tab_all(mut data: RefAny, _: CallbackInfo) -> Update {
    if let Some(mut s) = data.downcast_mut::<AppState>() { s.active_tab = TabFilter::All; }
    Update::RefreshDom
}

extern "C" fn on_tab_active(mut data: RefAny, _: CallbackInfo) -> Update {
    if let Some(mut s) = data.downcast_mut::<AppState>() { s.active_tab = TabFilter::Active; }
    Update::RefreshDom
}

extern "C" fn on_tab_completed(mut data: RefAny, _: CallbackInfo) -> Update {
    if let Some(mut s) = data.downcast_mut::<AppState>() { s.active_tab = TabFilter::Completed; }
    Update::RefreshDom
}

fn tab_div(label: &str, is_active: bool, data: RefAny, cb: CallbackType) -> Dom {
    let weight = if is_active { "bold" } else { "normal" };
    let style = format!(
        "color: {C_TEXT}; font-size: 14px; font-weight: {weight}; \
         padding-left: 8px; padding-right: 8px; background-color: transparent;"
    );
    let mut div = Dom::create_text(label)
        .with_inline_style(style.as_str());
    div.add_callback(EventFilter::Hover(HoverEventFilter::LeftMouseUp), data, cb);
    div
}

pub fn build_tabs(state: &AppState, data: RefAny) -> Dom {
    let all_btn      = tab_div("All",       state.active_tab == TabFilter::All,       data.clone(), on_tab_all);
    let active_btn   = tab_div("Active",    state.active_tab == TabFilter::Active,    data.clone(), on_tab_active);
    let completed_btn= tab_div("Completed", state.active_tab == TabFilter::Completed, data.clone(), on_tab_completed);
    Dom::create_div()
        .with_inline_style("flex-direction: row; margin-bottom: 3px;")
        .with_child(all_btn)
        .with_child(active_btn)
        .with_child(completed_btn)
}