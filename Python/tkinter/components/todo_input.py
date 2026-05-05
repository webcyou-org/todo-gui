import tkinter as tk
from typing import Callable

from theme import (
    C_BG, C_INPUT, C_WHITE, C_MUTED, C_ACCENT, FONT_NORMAL, rounded_rect,
)

_HEIGHT = 35


class TodoInput(tk.Canvas):
    def __init__(self, parent: tk.Widget, on_add: Callable[[str], None]):
        super().__init__(parent, bg=C_BG, height=_HEIGHT, highlightthickness=0)
        self._on_add = on_add
        self._has_placeholder = True
        self._rect_id = None
        self._win_id = None
        self._build()
        self.bind("<Configure>", self._redraw)

    def _build(self):
        self._entry = tk.Entry(
            self,
            bg=C_INPUT,
            fg=C_MUTED,
            insertbackground=C_WHITE,
            font=FONT_NORMAL,
            relief="flat",
            bd=0,
            highlightthickness=0,
        )
        self._entry.insert(0, "Add Task")
        self._entry.bind("<FocusIn>", self._on_focus_in)
        self._entry.bind("<FocusOut>", self._on_focus_out)
        self._entry.bind("<Return>", self._on_enter)

    def _redraw(self, _=None, border_color: str = ""):
        w = self.winfo_width()
        h = self.winfo_height() or _HEIGHT

        if self._rect_id:
            self.delete(self._rect_id)
        # Inset by 1px so the border stroke is never clipped at canvas edges
        m = 1
        self._rect_id = rounded_rect(
            self, m, m, w - m, h - m,
            fill=C_INPUT,
            outline=border_color,
            width=1 if border_color else 0,
        )

        if self._win_id is None:
            pad = 16
            self._win_id = self.create_window(
                pad, h // 2,
                window=self._entry,
                anchor="w",
                width=w - pad * 2,
                height=h - 6,
            )
        else:
            pad = 16
            self.itemconfig(self._win_id, width=w - pad * 2)

    def _draw_border(self, color: str):
        self._redraw(border_color=color)

    def _on_focus_in(self, _):
        if self._has_placeholder:
            self._entry.delete(0, tk.END)
            self._entry.config(fg=C_WHITE)
            self._has_placeholder = False
        self._draw_border(C_ACCENT)

    def _on_focus_out(self, _):
        if not self._entry.get().strip():
            self._entry.insert(0, "Add Task")
            self._entry.config(fg=C_MUTED)
            self._has_placeholder = True
        self._draw_border("")

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
            self.after(1, lambda: self.winfo_toplevel().focus_set())