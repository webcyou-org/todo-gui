use dioxus::prelude::*;
use crate::data::TabFilter;

#[component]
pub fn TabMenu(mut active_tab: Signal<TabFilter>) -> Element {
    rsx! {
        div {
            style: "display: flex; margin-bottom: 3px;",
            for tab in [TabFilter::All, TabFilter::Active, TabFilter::Completed] {
                {
                    let is_active = *active_tab.read() == tab;
                    let label = tab.label();
                    rsx! {
                        button {
                            class: if is_active { "tab-btn active" } else { "tab-btn" },
                            onclick: move |_| active_tab.set(tab.clone()),
                            "{label}"
                        }
                    }
                }
            }
        }
    }
}