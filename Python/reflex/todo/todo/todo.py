"""Todo application."""
import reflex as rx
from .state import TodoState
from .theme import BG, WHITE
from .components import todo_input, tab_menu, todo_list


def index() -> rx.Component:
    return rx.box(
        rx.box(
            rx.text(
                "ToDo",
                color=WHITE,
                font_size="18px",
                font_weight="bold",
                margin_bottom="14px",
            ),
            todo_input(),
            tab_menu(),
            todo_list(),
            padding="10px 24px",
            width="800px",
            height="600px",
            background_color=BG,
            overflow="hidden",
            display="flex",
            flex_direction="column",
        ),
        display="flex",
        justify_content="center",
        background_color=BG,
        min_height="100vh",
    )


app = rx.App(
    style={
        "background_color": BG,
        "font_family": "sans-serif",
    }
)
app.add_page(index)