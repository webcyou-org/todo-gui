import warnings
warnings.filterwarnings("ignore")

import sys
import os
sys.path.insert(0, os.path.dirname(__file__))

import pyforms
from pyforms import BaseWidget
from PyQt5.QtWidgets import QWidget, QVBoxLayout, QLabel, QSizePolicy
from data import TodoModel, MenuModel, TabFilter
from theme import Theme
from widgets.todo_input import TodoInput
from widgets.tab_menu import TabMenu
from widgets.todo_list import TodoList


class TodoApp(BaseWidget):
    def __init__(self):
        super().__init__("ToDo")
        self._todo_model = TodoModel()
        self._menu_model = MenuModel()

    def init_form(self):
        self.setFixedSize(800, 600)
        self.setStyleSheet(f"background-color: {Theme.BG};")

        root = QWidget()
        root.setStyleSheet(f"background-color: {Theme.BG};")
        root_layout = QVBoxLayout(root)
        root_layout.setContentsMargins(24, 10, 24, 10)
        root_layout.setSpacing(0)

        # Title
        title = QLabel("ToDo")
        title.setStyleSheet(
            f"color: {Theme.WHITE}; font-size: 18px; font-weight: bold;"
            " background: transparent;"
        )
        root_layout.addWidget(title)
        root_layout.addSpacing(14)

        # Input
        self._input_widget = TodoInput(self._on_add_todo)
        root_layout.addWidget(self._input_widget)
        root_layout.addSpacing(14)

        # Tabs
        self._tab_menu = TabMenu(self._on_tab_change)
        root_layout.addWidget(self._tab_menu)
        root_layout.addSpacing(3)

        # Todo list
        self._todo_list = TodoList(self._on_toggle)
        root_layout.addWidget(self._todo_list)

        self.layout().addWidget(root)
        self._refresh_list()

    def _refresh_list(self):
        self._todo_list.refresh(self._todo_model.filtered(self._menu_model.active_tab))

    def _on_add_todo(self, task: str):
        self._todo_model.add_todo(task)
        self._refresh_list()

    def _on_tab_change(self, f: TabFilter):
        self._menu_model.active_tab = f
        self._tab_menu.set_active(f)
        self._refresh_list()

    def _on_toggle(self, id: int):
        self._todo_model.toggle(id)
        self._refresh_list()


if __name__ == "__main__":
    pyforms.start_app(TodoApp, geometry=(100, 100, 800, 600))