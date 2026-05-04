use druid::widget::{CrossAxisAlignment, Either, Flex, Label};
use druid::{FontDescriptor, FontFamily, FontWeight, Widget, WidgetExt};

use crate::data::{AppState, TabFilter};
use crate::theme::TEXT_MAIN;

fn tab_button(label: &'static str, filter: TabFilter) -> impl Widget<AppState> {
    let bold_font   = FontDescriptor::new(FontFamily::SYSTEM_UI).with_weight(FontWeight::BOLD).with_size(14.0);
    let normal_font = FontDescriptor::new(FontFamily::SYSTEM_UI).with_size(14.0);
    let check_filter = filter.clone();
    let click_filter = filter;

    Either::new(
        move |data: &AppState, _| data.active_tab == check_filter,
        Label::new(label).with_font(bold_font).with_text_color(TEXT_MAIN),
        Label::new(label).with_font(normal_font).with_text_color(TEXT_MAIN),
    )
    .fix_height(28.0)
    .padding((8.0, 0.0))
    .on_click(move |_ctx, data: &mut AppState, _| {
        data.active_tab = click_filter.clone();
    })
}

pub fn build_tabs() -> impl Widget<AppState> {
    Flex::row()
        .cross_axis_alignment(CrossAxisAlignment::Center)
        .with_child(tab_button("All",       TabFilter::All))
        .with_child(tab_button("Active",    TabFilter::Active))
        .with_child(tab_button("Completed", TabFilter::Completed))
}