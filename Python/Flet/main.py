import sys
import os
sys.path.insert(0, os.path.dirname(__file__))

import flet as ft
from data import TodoModel, MenuModel, TabFilter
from theme import Theme
from components.todo_input import build_todo_input
from components.tab_menu import build_tab_menu
from components.todo_list import build_todo_list


def main(page: ft.Page):
    todo_model = TodoModel()
    menu_model = MenuModel()

    page.title = "ToDo"
    page.bgcolor = Theme.BG
    page.padding = 0
    page.window.width = 800
    page.window.height = 600
    page.window.resizable = False

    def on_add_todo(e):
        text = input_field.value.strip()
        if not text:
            return
        todo_model.add_todo(text)
        input_field.value = ""
        input_field.update()
        refresh_list()

    def on_toggle(id: int):
        todo_model.toggle_completed(id)
        refresh_list()

    def on_tab_change(f: TabFilter):
        menu_model.active_tab = f
        new_tab = build_tab_menu(menu_model.active_tab, on_tab_change)
        tab_row.controls = new_tab.controls
        tab_row.update()
        refresh_list()

    def refresh_list():
        todos = todo_model.filtered_todos(menu_model.active_tab)
        new_items = build_todo_list(todos, on_toggle)
        todo_list.controls = new_items.controls
        todo_list.update()

    input_field = build_todo_input(on_add_todo)

    tab_row = build_tab_menu(menu_model.active_tab, on_tab_change)

    initial_todos = todo_model.filtered_todos(menu_model.active_tab)
    todo_list = build_todo_list(initial_todos, on_toggle)

    content = ft.Column(
        controls=[
            ft.Text("ToDo", size=18, weight=ft.FontWeight.BOLD, color=Theme.WHITE),
            ft.Container(height=14),
            input_field,
            ft.Container(height=14),
            tab_row,
            ft.Container(height=3),
            todo_list,
        ],
        spacing=0,
        horizontal_alignment=ft.CrossAxisAlignment.STRETCH,
        expand=True,
    )

    page.add(
        ft.Container(
            content=content,
            bgcolor=Theme.BG,
            padding=ft.Padding.symmetric(horizontal=24, vertical=10),
            expand=True,
        )
    )


ft.run(main)