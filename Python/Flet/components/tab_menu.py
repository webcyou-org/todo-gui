import flet as ft
from typing import Callable
from data import TabFilter
from theme import Theme

TAB_LABELS = [
    (TabFilter.ALL,       "All"),
    (TabFilter.ACTIVE,    "Active"),
    (TabFilter.COMPLETED, "Completed"),
]


def build_tab_menu(
    active: TabFilter,
    on_change: Callable[[TabFilter], None],
) -> ft.Row:
    buttons = []
    for filter_val, label in TAB_LABELS:
        is_active = filter_val == active

        def make_handler(f):
            def handler(e):
                on_change(f)
            return handler

        btn = ft.GestureDetector(
            content=ft.Container(
                content=ft.Text(
                    label,
                    size=14,
                    weight=ft.FontWeight.BOLD if is_active else ft.FontWeight.NORMAL,
                    color=Theme.TEXT,
                ),
                padding=ft.Padding.symmetric(horizontal=8),
                height=28,
                alignment=ft.Alignment(-1, 0),
            ),
            on_tap=make_handler(filter_val),
            mouse_cursor=ft.MouseCursor.CLICK,
        )
        buttons.append(btn)

    return ft.Row(controls=buttons, spacing=0, height=28)