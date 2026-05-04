import tkinter as tk

from data import MenuModel, TabFilter, TodoModel
from theme import C_BG, C_WHITE, FONT_TITLE
from components.todo_input import TodoInput
from components.tabs import TabMenu
from components.todo_list import TodoList


class App(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("ToDo")
        self.geometry("800x600")
        self.resizable(False, False)
        self.configure(bg=C_BG)

        self.todo_model = TodoModel()
        self.menu_model = MenuModel()

        self._build()

    def _build(self):
        main = tk.Frame(self, bg=C_BG)
        main.pack(fill=tk.BOTH, expand=True, padx=24, pady=10)

        # Title
        tk.Label(
            main, text="ToDo",
            bg=C_BG, fg=C_WHITE, font=FONT_TITLE,
        ).pack(anchor="w", pady=(0, 10))

        # Input
        TodoInput(main, on_add=self._on_add).pack(fill=tk.X)

        # Tabs
        self._tab_menu = TabMenu(
            main,
            menu_model=self.menu_model,
            on_change=self._on_tab_change,
        )
        self._tab_menu.pack(fill=tk.X, pady=(10, 0))

        # Todo list
        self._todo_list = TodoList(main, self.todo_model, self.menu_model)
        self._todo_list.pack(fill=tk.BOTH, expand=True, pady=(10, 0))

    def _on_add(self, task: str):
        self.todo_model.add_todo(task)
        self._todo_list.refresh()

    def _on_tab_change(self, tab: TabFilter):
        self.menu_model.set_active_tab(tab)
        self._tab_menu.refresh()
        self._todo_list.refresh()


if __name__ == "__main__":
    App().mainloop()