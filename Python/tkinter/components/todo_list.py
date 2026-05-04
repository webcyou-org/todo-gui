import tkinter as tk

from data import MenuModel, Todo, TodoModel
from theme import (
    C_BG, C_SURFACE, C_TEXT, C_MUTED, C_ACCENT, C_WHITE, C_CB_BORDER,
    FONT_NORMAL, FONT_STRIKE, rounded_rect,
)


class TodoList(tk.Frame):
    def __init__(self, parent: tk.Widget, todo_model: TodoModel, menu_model: MenuModel):
        super().__init__(parent, bg=C_BG)
        self._todo_model = todo_model
        self._menu_model = menu_model
        self._build()

    def _build(self):
        self._canvas = tk.Canvas(self, bg=C_BG, highlightthickness=0)
        self._scrollbar = tk.Scrollbar(self, orient="vertical", command=self._canvas.yview)

        self._inner = tk.Frame(self._canvas, bg=C_BG)
        self._inner.bind(
            "<Configure>",
            lambda e: self._canvas.configure(scrollregion=self._canvas.bbox("all")),
        )

        win_id = self._canvas.create_window((0, 0), window=self._inner, anchor="nw")
        self._canvas.configure(yscrollcommand=self._scrollbar.set)
        self._canvas.bind(
            "<Configure>",
            lambda e: self._canvas.itemconfig(win_id, width=e.width),
        )
        self._canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

        def on_wheel(e):
            self._canvas.yview_scroll(int(-1 * (e.delta / 120)), "units")

        # bind_all は IMK と競合するため、カーソルが乗った時だけ有効化する
        self._canvas.bind("<Enter>", lambda _: self._canvas.bind_all("<MouseWheel>", on_wheel))
        self._canvas.bind("<Leave>", lambda _: self._canvas.unbind_all("<MouseWheel>"))

        self.refresh()

    def refresh(self):
        for w in self._inner.winfo_children():
            w.destroy()

        todos = self._todo_model.get_filtered_todos(self._menu_model.get_active_tab())
        for todo in todos:
            _make_todo_row(self._inner, todo, self._on_toggle)

        self.after(10, self._sync_scrollbar)

    def _on_toggle(self, todo: Todo):
        self._todo_model.change_completed(todo)
        self.refresh()

    def _sync_scrollbar(self):
        self._inner.update_idletasks()
        if self._inner.winfo_reqheight() > self._canvas.winfo_height():
            self._scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
        else:
            self._scrollbar.pack_forget()


_ROW_H = 35


def _make_todo_row(parent: tk.Widget, todo: Todo, on_toggle):
    row = tk.Canvas(parent, height=_ROW_H, bg=C_BG, highlightthickness=0)
    row.pack(fill=tk.X, pady=(0, 5))

    def _draw(event=None):
        row.delete("all")
        w = row.winfo_width()
        h = _ROW_H

        rounded_rect(row, 0, 0, w, h, fill=C_SURFACE, outline="")

        # Circular checkbox
        cb = tk.Canvas(row, width=16, height=16, bg=C_SURFACE, highlightthickness=0)
        if todo.is_completed:
            cb.create_oval(1, 1, 15, 15, fill=C_ACCENT, outline=C_ACCENT)
            cb.create_line(4, 8, 7, 11, fill=C_WHITE, width=1.5, capstyle=tk.ROUND)
            cb.create_line(7, 11, 12, 5, fill=C_WHITE, width=1.5, capstyle=tk.ROUND)
        else:
            cb.create_oval(1, 1, 15, 15, fill="", outline=C_CB_BORDER, width=1.5)

        row.create_window(10, h // 2, window=cb, anchor="w")

        label = tk.Label(
            row,
            text=todo.task,
            bg=C_SURFACE,
            fg=C_MUTED if todo.is_completed else C_TEXT,
            font=FONT_STRIKE if todo.is_completed else FONT_NORMAL,
            anchor="w",
        )
        row.create_window(36, h // 2, window=label, anchor="w", width=w - 46)

        def toggle(_=None, t=todo):
            on_toggle(t)

        for w_widget in (row, cb, label):
            w_widget.bind("<Button-1>", toggle)

    row.bind("<Configure>", _draw)