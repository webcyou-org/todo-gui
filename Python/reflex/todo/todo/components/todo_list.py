"""Todo list component."""
import reflex as rx
from ..state import TodoState, Todo
from .. import theme


def todo_item(todo: Todo) -> rx.Component:
    return rx.hstack(
        rx.cond(
            todo.is_completed,
            rx.box(
                rx.text(
                    "✓",
                    color=theme.ACCENT,
                    font_size="10px",
                    line_height="1",
                ),
                width=theme.CB_SIZE,
                height=theme.CB_SIZE,
                border_radius="50%",
                background_color="transparent",
                border=f"2px solid {theme.CB_BDR}",
                display="flex",
                align_items="center",
                justify_content="center",
                flex_shrink="0",
                cursor="pointer",
                on_click=TodoState.toggle_todo(todo.id),
            ),
            rx.box(
                width=theme.CB_SIZE,
                height=theme.CB_SIZE,
                border_radius="50%",
                border=f"2px solid {theme.CB_BDR}",
                flex_shrink="0",
                cursor="pointer",
                on_click=TodoState.toggle_todo(todo.id),
            ),
        ),
        rx.text(
            todo.task,
            color=rx.cond(todo.is_completed, theme.MUTED, theme.TEXT),
            text_decoration=rx.cond(todo.is_completed, "line-through", "none"),
            font_size="14px",
        ),
        align="center",
        spacing="0",
        gap=theme.CB_MR,
        background_color=theme.SURFACE,
        height=theme.ITEM_H,
        border_radius="4px",
        padding="0 10px",
        width="100%",
    )


def todo_list() -> rx.Component:
    return rx.scroll_area(
        rx.vstack(
            rx.foreach(TodoState.filtered_todos, todo_item),
            spacing="0",
            gap=theme.ITEM_MB,
            width="100%",
        ),
        flex="1",
        overflow_y="auto",
    )