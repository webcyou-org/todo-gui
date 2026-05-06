"""Scrollable todo list widget."""
import tkinter as tk
from typing import List, Callable
from data import Todo, TodoModel, TabFilter
from theme import Theme, FONT_NORMAL


class TodoListWidget:
    def __init__(self, canvas: tk.Canvas, todo_model: TodoModel,
                 get_active_tab: Callable[[], TabFilter]):
        self._canvas = canvas
        self._todo_model = todo_model
        self._get_active_tab = get_active_tab
        self._item_frames: list = []

        self._inner = tk.Frame(canvas, bg=Theme.BG)
        self._win_id = canvas.create_window(0, 0, anchor="nw", window=self._inner)

        self._inner.bind("<Configure>", self._on_inner_configure)
        canvas.bind("<Configure>", self._on_canvas_configure)
        canvas.bind("<MouseWheel>",
                    lambda e: canvas.yview_scroll(-1 * (e.delta // 120), "units"))
        canvas.configure(bg=Theme.BG, highlightthickness=0, bd=0)

    def attach_scrollbar(self, scrollbar: tk.Scrollbar):
        self._canvas.configure(yscrollcommand=scrollbar.set)
        scrollbar.configure(command=self._canvas.yview)

    def _on_inner_configure(self, _e):
        self._canvas.configure(scrollregion=self._canvas.bbox("all"))

    def _on_canvas_configure(self, e):
        self._canvas.itemconfig(self._win_id, width=e.width)

    def _make_toggle_cb(self, todo_id: int):
        def cb(event=None):
            self._todo_model.toggle(todo_id)
            self.refresh()
        return cb

    def refresh(self):
        for f in self._item_frames:
            f.destroy()
        self._item_frames = []

        for todo in self._todo_model.filtered(self._get_active_tab()):
            row = tk.Frame(self._inner, bg=Theme.SURFACE, height=Theme.ITEM_H)
            row.pack(fill="x", pady=(0, Theme.ITEM_MB))
            row.pack_propagate(False)

            # Circular checkbox
            cb_cv = tk.Canvas(row, width=Theme.CB_SIZE, height=Theme.CB_SIZE,
                              bg=Theme.SURFACE, highlightthickness=0)
            cb_cv.place(x=Theme.CB_PAD_L, y=(Theme.ITEM_H - Theme.CB_SIZE) // 2)

            if todo.is_completed:
                cb_cv.create_oval(0, 0, Theme.CB_SIZE, Theme.CB_SIZE,
                                  fill=Theme.ACCENT, outline="")
                cx, cy = Theme.CB_SIZE / 2.0, Theme.CB_SIZE / 2.0
                cb_cv.create_line(cx-4, cy, cx-1, cy+3, cx+4, cy-3,
                                  fill=Theme.WHITE, width=1.5,
                                  joinstyle="round", capstyle="round")
            else:
                cb_cv.create_oval(1, 1, Theme.CB_SIZE-1, Theme.CB_SIZE-1,
                                  fill="", outline=Theme.CB_BDR, width=2)

            toggle = self._make_toggle_cb(todo.id)
            cb_cv.bind("<Button-1>", toggle)

            # Task label
            tx = Theme.CB_PAD_L + Theme.CB_SIZE + Theme.CB_MR
            font = (*FONT_NORMAL[:2], "overstrike") if todo.is_completed else FONT_NORMAL
            lbl = tk.Label(
                row,
                text=todo.task,
                bg=Theme.SURFACE,
                fg=Theme.MUTED if todo.is_completed else Theme.TEXT,
                font=font,
                anchor="w",
            )
            lbl.place(x=tx, y=0, relheight=1.0)
            self._item_frames.append(row)

        self._inner.update_idletasks()
        self._canvas.configure(scrollregion=self._canvas.bbox("all"))