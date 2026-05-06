#!/usr/bin/env python3
import toga
from toga.style import Pack
from toga.style.pack import BOLD, COLUMN

from data import MenuModel, TodoModel
from theme import C_BG, C_WHITE
from widgets.tabs import make_tabs
from widgets.todo_input import make_input
from widgets.todo_item import make_todo_item


def startup(app: toga.App) -> toga.Widget:
    # Override auto-created window with 800×600
    app.main_window = toga.MainWindow(title="ToDo", size=(800, 600))

    todo_model = TodoModel()
    menu_model = MenuModel()

    # ── Root layout ───────────────────────────────────────────────────────────
    # outer_box fills window entirely with dark bg (prevents white gaps from margin)
    outer_box = toga.Box(style=Pack(
        direction=COLUMN,
        background_color=C_BG,
        flex=1,
    ))
    # main_box carries the content insets
    main_box = toga.Box(style=Pack(
        direction=COLUMN,
        margin_top=10,
        margin_bottom=10,
        margin_left=24,
        margin_right=24,
        background_color=C_BG,
        flex=1,
    ))
    outer_box.add(main_box)

    # Title
    main_box.add(toga.Label(
        "ToDo",
        style=Pack(
            font_size=18,
            font_weight=BOLD,
            color=C_WHITE,
            background_color=C_BG,
            margin_bottom=14,
        ),
    ))

    # ── List box (defined early — referenced by refresh_list) ─────────────────
    list_box = toga.Box(style=Pack(direction=COLUMN, background_color=C_BG, flex=1))

    def refresh_list() -> None:
        for child in list(list_box.children):
            list_box.remove(child)
        for todo in todo_model.get_filtered_todos(menu_model.get_active_tab()):
            list_box.add(make_todo_item(todo, todo_model, refresh_list))

    # ── Input ─────────────────────────────────────────────────────────────────
    def on_add(task: str) -> None:
        todo_model.add_todo(task)
        refresh_list()

    main_box.add(make_input(on_add))

    # ── Tabs ──────────────────────────────────────────────────────────────────
    main_box.add(make_tabs(menu_model, refresh_list))

    # ── Scroll container ──────────────────────────────────────────────────────
    main_box.add(toga.ScrollContainer(
        content=list_box,
        horizontal=False,
        style=Pack(flex=1),
    ))

    refresh_list()

    # Return outer_box — Toga sets main_window.content and calls show()
    return outer_box


def main() -> toga.App:
    return toga.App("ToDo", "org.beeware.todo", startup=startup)


if __name__ == "__main__":
    main().main_loop()