import tkinter as tk
from typing import Callable

from ..theme import (
    C_INPUT, C_WHITE, C_MUTED, C_ACCENT, FONT_NORMAL,
)


class TodoInput(tk.Frame):
    def __init__(self, parent: tk.Widget, on_add: Callable[[str], None]):
        super().__init__(parent, bg=C_INPUT)
        self._on_add = on_add
        self._has_placeholder = True
        self._build()

    def _build(self):
        self._entry = tk.Entry(
            self,
            bg=C_INPUT,
            fg=C_MUTED,
            insertbackground=C_WHITE,
            font=FONT_NORMAL,
            relief="flat",
            bd=0,
            highlightthickness=1,
            highlightcolor=C_ACCENT,
            highlightbackground=C_INPUT,
        )
        self._entry.pack(fill=tk.X, ipady=8)
        self._entry.insert(0, "Add Task")

        self._entry.bind("<FocusIn>", self._on_focus_in)
        self._entry.bind("<FocusOut>", self._on_focus_out)
        self._entry.bind("<Return>", self._on_enter)

    def _on_focus_in(self, _):
        if self._has_placeholder:
            self._entry.delete(0, tk.END)
            self._entry.config(fg=C_WHITE)
            self._has_placeholder = False

    def _on_focus_out(self, _):
        if not self._entry.get().strip():
            self._entry.insert(0, "Add Task")
            self._entry.config(fg=C_MUTED)
            self._has_placeholder = True

    def _on_enter(self, _):
        if self._has_placeholder:
            return
        task = self._entry.get().strip()
        if task:
            self._on_add(task)
            self._entry.delete(0, tk.END)
            self._entry.insert(0, "Add Task")
            self._entry.config(fg=C_MUTED)
            self._has_placeholder = True
            self._entry.tk_focusNext().focus()