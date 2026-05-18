import flet as ft
from typing import Callable, List
from data import Todo
from theme import Theme


def build_checkbox(completed: bool) -> ft.Container:
    if completed:
        return ft.Container(
            content=ft.Text("✓", size=10, color=Theme.ACCENT),
            width=16,
            height=16,
            border_radius=8,
            border=ft.Border.all(2, Theme.CB_BDR),
            alignment=ft.Alignment(0, 0),
        )
    else:
        return ft.Container(
            width=16,
            height=16,
            border_radius=8,
            border=ft.Border.all(2, Theme.CB_BDR),
        )


def build_todo_item(todo: Todo, on_toggle: Callable[[int], None]) -> ft.Container:
    def handle_toggle(e):
        on_toggle(todo.id)

    checkbox = build_checkbox(todo.is_completed)

    label = ft.Text(
        todo.task,
        size=14,
        color=Theme.MUTED if todo.is_completed else Theme.TEXT,
        style=ft.TextStyle(
            decoration=ft.TextDecoration.LINE_THROUGH if todo.is_completed else ft.TextDecoration.NONE,
        ),
    )

    row = ft.Row(
        controls=[
            ft.GestureDetector(
                content=checkbox,
                on_tap=handle_toggle,
                mouse_cursor=ft.MouseCursor.CLICK,
            ),
            ft.Container(width=18),
            label,
        ],
        spacing=0,
        vertical_alignment=ft.CrossAxisAlignment.CENTER,
    )

    return ft.Container(
        content=row,
        bgcolor=Theme.SURFACE,
        border_radius=4,
        padding=10,
        height=35,
        margin=ft.Margin(0, 0, 0, 5),
    )


def build_todo_list(
    todos: List[Todo],
    on_toggle: Callable[[int], None],
) -> ft.Column:
    items = [build_todo_item(t, on_toggle) for t in todos]
    return ft.Column(
        controls=items,
        spacing=0,
        scroll=ft.ScrollMode.AUTO,
        expand=True,
    )