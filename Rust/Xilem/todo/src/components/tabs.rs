use xilem::masonry::properties::Padding;
use xilem::style::Style as _;
use xilem::view::{button, flex_row, label};
use xilem::{Color, FontWeight, WidgetView};

use crate::data::{AppState, TabFilter};
use crate::theme::C_TEXT;

fn tab_button(active_tab: TabFilter, filter: TabFilter) -> impl WidgetView<AppState> {
    let is_active = active_tab == filter;
    button(
        label(filter.label())
            .text_size(14.)
            .weight(if is_active { FontWeight::BOLD } else { FontWeight::NORMAL })
            .color(C_TEXT),
        move |state: &mut AppState| state.active_tab = filter,
    )
    .background_color(Color::TRANSPARENT)
    .border(Color::TRANSPARENT, 0.)
    .padding(Padding::from_vh(4., 8.))
}

pub fn tab_menu(active_tab: TabFilter) -> impl WidgetView<AppState> {
    flex_row((
        tab_button(active_tab, TabFilter::All),
        tab_button(active_tab, TabFilter::Active),
        tab_button(active_tab, TabFilter::Completed),
    ))
}