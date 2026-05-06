"""Tab menu component."""
import reflex as rx
from ..state import TodoState
from .. import theme

TABS = [
    ("all",       "All"),
    ("active",    "Active"),
    ("completed", "Completed"),
]


def tab_menu() -> rx.Component:
    return rx.hstack(
        *[
            rx.text(
                label,
                color=theme.TEXT,
                font_size="14px",
                font_weight=rx.cond(
                    TodoState.active_tab == tab_id,
                    "bold",
                    "normal",
                ),
                line_height="28px",
                padding="0 8px",
                cursor="pointer",
                on_click=TodoState.set_tab(tab_id),
            )
            for tab_id, label in TABS
        ],
        spacing="0",
        margin_bottom="3px",
    )