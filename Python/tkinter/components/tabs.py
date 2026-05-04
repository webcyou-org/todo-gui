import tkinter as tk
from typing import Callable

from data import MenuModel, TabFilter
from theme import C_BG, C_TEXT, FONT_NORMAL, FONT_BOLD


class TabMenu(tk.Frame):
    def __init__(self, parent: tk.Widget, menu_model: MenuModel,
                 on_change: Callable[[TabFilter], None]):
        super().__init__(parent, bg=C_BG)
        self._menu_model = menu_model
        self._on_change = on_change
        self.refresh()

    def refresh(self):
        for w in self.winfo_children():
            w.destroy()

        active = self._menu_model.get_active_tab()
        for tab in self._menu_model.get_tab_list():
            is_active = tab == active
            btn = tk.Label(
                self,
                text=tab.value,
                bg=C_BG,
                fg=C_TEXT,
                font=FONT_BOLD if is_active else FONT_NORMAL,
                padx=8,
                pady=4,
                cursor="hand2",
            )
            btn.pack(side=tk.LEFT)
            btn.bind("<Button-1>", lambda _, t=tab: self._on_change(t))