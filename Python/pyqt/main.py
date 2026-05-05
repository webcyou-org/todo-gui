import sys
from PyQt6.QtWidgets import QApplication, QWidget, QVBoxLayout, QLabel
from PyQt6.QtGui import QPalette, QFont

import theme
from data import TodoModel, MenuModel, TabFilter
from components.todo_input import TodoInput
from components.tab_menu import TabMenu
from components.todo_list import TodoList


class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self._todo_model = TodoModel()
        self._menu_model = MenuModel()
        self.setWindowTitle("ToDo")
        self.setFixedSize(800, 600)
        self._setup_ui()
        self._refresh_list()
        self._refresh_tabs()

    def _setup_ui(self):
        pal = self.palette()
        pal.setColor(QPalette.ColorRole.Window, theme.C_BG)
        self.setPalette(pal)
        self.setAutoFillBackground(True)

        root = QVBoxLayout(self)
        root.setContentsMargins(theme.CONTENT_H, theme.CONTENT_V,
                                theme.CONTENT_H, theme.CONTENT_V)
        root.setSpacing(0)

        # Title
        title = QLabel("ToDo")
        tf = QFont()
        tf.setPixelSize(18)
        tf.setBold(True)
        title.setFont(tf)
        tp = title.palette()
        tp.setColor(QPalette.ColorRole.WindowText, theme.C_WHITE)
        title.setPalette(tp)
        root.addWidget(title)
        root.addSpacing(14)

        # Input
        self._input = TodoInput()
        self._input.returnPressed.connect(self._on_add_todo)
        root.addWidget(self._input)
        root.addSpacing(14)

        # Tabs
        self._tab_menu = TabMenu()
        self._tab_menu.tab_clicked.connect(self._on_tab_clicked)
        root.addWidget(self._tab_menu)
        root.addSpacing(3)

        # List
        self._todo_list = TodoList()
        self._todo_list.toggle_requested.connect(self._on_toggle)
        root.addWidget(self._todo_list, 1)

    def _on_add_todo(self):
        text = self._input.text().strip()
        if not text:
            return
        self._todo_model.add_todo(text)
        self._input.clear()
        self._refresh_list()

    def _on_toggle(self, todo_id: int):
        self._todo_model.toggle_completed(todo_id)
        self._refresh_list()

    def _on_tab_clicked(self, tab: TabFilter):
        self._menu_model.active_tab = tab
        self._refresh_tabs()
        self._refresh_list()

    def _refresh_list(self):
        todos = self._todo_model.filtered_todos(self._menu_model.active_tab)
        self._todo_list.refresh(todos)

    def _refresh_tabs(self):
        self._tab_menu.set_active(self._menu_model.active_tab)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    w = MainWindow()
    w.show()
    sys.exit(app.exec())