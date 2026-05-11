use vizia::prelude::*;
use crate::data::{AppData, AppEvent};

const TABS: [&str; 3] = ["All", "Active", "Completed"];

pub fn build_tabs(cx: &mut Context) {
    HStack::new(cx, |cx| {
        for (i, label) in TABS.iter().enumerate() {
            Button::new(cx, |cx| Label::new(cx, *label))
                .class("tab-btn")
                .toggle_class("active", AppData::active_tab.map(move |tab| *tab == i))
                .on_press(move |cx| cx.emit(AppEvent::SetActiveTab(i)));
        }
    })
    .class("tab-bar");
}