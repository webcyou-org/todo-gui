import sys
import os
sys.path.insert(0, os.path.dirname(__file__))

import remi.gui as gui
from remi import start, App

from data import TodoModel, MenuModel, TabFilter
from theme import Theme
from widgets.todo_input import build_todo_input
from widgets.tab_menu import TabMenu
from widgets.todo_list import TodoList


class TodoApp(App):
    def main(self):
        self._todo_model = TodoModel()
        self._menu_model = MenuModel()

        # Page shell
        page = gui.VBox()
        page.style.update({
            'width': '100%',
            'min-height': '100vh',
            'background-color': Theme.BG,
            'align-items': 'center',
            'justify-content': 'flex-start',
            'margin': '0',
            'padding': '0',
        })

        # 800×600 container
        outer = gui.VBox()
        outer.style.update({
            'width': '800px',
            'height': '600px',
            'background-color': Theme.BG,
            'padding': '10px 24px',
            'box-sizing': 'border-box',
            'overflow': 'hidden',
        })

        # Title
        title = gui.Label("ToDo")
        title.style.update({
            'color': Theme.WHITE,
            'font-size': '18px',
            'font-weight': 'bold',
            'margin-bottom': '14px',
            'align-self': 'flex-start',
        })
        outer.append(title)

        # Input
        self._input = build_todo_input(self._on_add_todo)
        outer.append(self._input)

        # Tabs
        self._tab_menu = TabMenu(self._on_tab_change)
        self._tab_menu.set_active(self._menu_model.active_tab)
        outer.append(self._tab_menu)

        # Todo list
        self._todo_list = TodoList(self._on_toggle)
        outer.append(self._todo_list)

        page.append(outer)
        self._refresh_list()
        return page

    def _refresh_list(self):
        self._todo_list.refresh(
            self._todo_model.filtered(self._menu_model.active_tab)
        )

    def _on_add_todo(self, task: str):
        self._todo_model.add(task)
        self._refresh_list()

    def _on_tab_change(self, f: TabFilter):
        self._menu_model.active_tab = f
        self._tab_menu.set_active(f)
        self._refresh_list()

    def _on_toggle(self, todo_id: int):
        self._todo_model.toggle(todo_id)
        self._refresh_list()


start(TodoApp, debug=False, address='0.0.0.0', port=8081, start_browser=False)