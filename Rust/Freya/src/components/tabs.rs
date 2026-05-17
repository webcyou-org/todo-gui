use freya::prelude::*;

use crate::data::TabFilter;
use crate::theme::*;

#[component]
pub fn TabMenu(
    active_tab: Signal<TabFilter>,
) -> Element {
    rsx!(
        rect {
            width: "100%",
            height: "28",
            direction: "horizontal",
            margin: "0 0 3 0",
            for tab in [TabFilter::All, TabFilter::Active, TabFilter::Completed] {
                {
                    let is_active = *active_tab.read() == tab;
                    rsx!(
                        rect {
                            key: "{tab:?}",
                            padding: "0 8",
                            height: "28",
                            cross_align: "center",
                            onclick: move |_| {
                                active_tab.set(tab);
                            },
                            label {
                                color: C_TEXT,
                                font_size: "14",
                                font_weight: if is_active { "bold" } else { "normal" },
                                "{tab.label()}"
                            }
                        }
                    )
                }
            }
        }
    )
}