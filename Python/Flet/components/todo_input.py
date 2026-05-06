import flet as ft
from theme import Theme


def build_todo_input(on_submit) -> ft.TextField:
    return ft.TextField(
        hint_text="Add Task",
        hint_style=ft.TextStyle(color=Theme.MUTED),
        bgcolor=Theme.INPUT,
        color=Theme.WHITE,
        border_radius=4,
        border=ft.InputBorder.OUTLINE,
        border_color="transparent",
        focused_border_color=Theme.ACCENT,
        border_width=1,
        focused_border_width=1,
        height=35,
        text_size=14,
        content_padding=ft.Padding.symmetric(horizontal=16, vertical=4),
        on_submit=on_submit,
        cursor_color=Theme.WHITE,
    )