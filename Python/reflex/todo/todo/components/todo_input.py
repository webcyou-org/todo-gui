"""Todo input field component."""
import reflex as rx
from ..state import TodoState
from .. import theme


def todo_input() -> rx.Component:
    return rx.form(
        rx.input(
            name="new_task",
            placeholder="Add Task",
            height=theme.ITEM_H,
            background_color=theme.INPUT,
            color=theme.WHITE,
            border_radius="4px",
            border="1px solid transparent",
            padding="4px 16px",
            font_size="14px",
            width="100%",
            _placeholder={"color": theme.MUTED},
            _focus={
                "outline": "none",
                "border": f"1px solid {theme.ACCENT}",
                "box_shadow": "none",
            },
        ),
        on_submit=TodoState.handle_submit,
        reset_on_submit=True,
        width="100%",
        margin_bottom="14px",
    )