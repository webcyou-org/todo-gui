use freya::prelude::*;

use crate::theme::*;

#[component]
pub fn TodoInput(
    value: Signal<String>,
    on_change: EventHandler<String>,
) -> Element {
    rsx!(
        rect {
            width: "100%",
            height: "35",
            margin: "0 0 14 0",
            direction: "horizontal",
            cross_align: "center",
            Input {
                value,
                placeholder: "Add Task",
                onchange: move |e: String| {
                    on_change.call(e);
                },
                width: "fill",
                theme: InputThemeWith {
                    background: Some(C_INPUT.into()),
                    hover_background: Some(C_INPUT.into()),
                    border_fill: Some("transparent".into()),
                    focus_border_fill: Some(C_ACCENT.into()),
                    corner_radius: Some("4".into()),
                    shadow: Some("none".into()),
                    margin: Some("0".into()),
                    font_theme: Some(FontThemeWith {
                        color: Some(C_WHITE.into()),
                    }),
                    placeholder_font_theme: Some(FontThemeWith {
                        color: Some(C_MUTED.into()),
                    }),
                },
            }
        }
    )
}