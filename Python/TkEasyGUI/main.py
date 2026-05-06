#!/opt/homebrew/bin/python3.9
import sys, os
sys.path.insert(0, os.path.dirname(__file__))

import TkEasyGUI as eg
import tkinter as tk
from tkinter import ttk

from data import TodoModel, MenuModel, TabFilter
from theme import Theme, FONT_TITLE, FONT_NORMAL, FONT_BOLD
from widgets.todo_list import TodoListWidget

# clam テーマは macOS でも background_color が効く
eg.set_theme("clam")


def main():
    todo_model = TodoModel()
    menu_model = MenuModel()

    # Tab ボタンは eg.Text + enable_events で背景色を確実に設定
    layout = [
        [eg.Text("ToDo", text_color=Theme.WHITE, font=FONT_TITLE,
                 background_color=Theme.BG, pad=(0, (0, 14)))],
        [eg.Input(
            key="new_task",
            background_color=Theme.INPUT,
            text_color=Theme.WHITE,
            font=FONT_NORMAL,
            expand_x=True,
            pad=(0, (0, 14)),
        )],
        [
            eg.Text("All",       key="tab_all",       font=FONT_BOLD,   enable_events=True,
                    text_color=Theme.TEXT, background_color=Theme.BG, pad=((0,0),(0,3))),
            eg.Text("Active",    key="tab_active",    font=FONT_NORMAL, enable_events=True,
                    text_color=Theme.TEXT, background_color=Theme.BG, pad=((0,0),(0,3))),
            eg.Text("Completed", key="tab_completed", font=FONT_NORMAL, enable_events=True,
                    text_color=Theme.TEXT, background_color=Theme.BG, pad=((0,0),(0,3))),
        ],
        [eg.Canvas(key="todo_canvas", background_color=Theme.BG,
                   size=(752, 450), expand_x=True, expand_y=True)],
    ]

    with eg.Window(
        "ToDo",
        layout,
        size=(800, 600),
        resizable=False,
        padding_x=24,
        padding_y=10,
    ) as window:
        # ── ウィンドウ全体の背景を上書き ────────────────────────────────
        win_root: tk.Toplevel = window.window
        win_root.configure(bg=Theme.BG)
        if hasattr(window, "frame"):
            window.frame.configure(bg=Theme.BG)

        # ── Input スタイル ────────────────────────────────────────────────
        input_widget: tk.Entry = window["new_task"].widget
        input_widget.configure(
            relief="flat",
            highlightthickness=1,
            highlightbackground=Theme.INPUT,
            highlightcolor=Theme.ACCENT,
            insertbackground=Theme.WHITE,
        )

        # ── Tab ラベルのカーソル ───────────────────────────────────────────
        for key in ("tab_all", "tab_active", "tab_completed"):
            window[key].widget.configure(cursor="hand2", padx=8)

        # ── Todo リスト ───────────────────────────────────────────────────
        canvas: tk.Canvas = window["todo_canvas"].widget
        scrollbar = tk.Scrollbar(win_root, orient="vertical")
        scrollbar.place(relx=1.0, rely=0.0, relheight=1.0, anchor="ne")

        todo_list = TodoListWidget(canvas, todo_model, lambda: menu_model.active_tab)
        todo_list.attach_scrollbar(scrollbar)
        todo_list.refresh()

        def update_tabs():
            for f, key in [
                (TabFilter.ALL,       "tab_all"),
                (TabFilter.ACTIVE,    "tab_active"),
                (TabFilter.COMPLETED, "tab_completed"),
            ]:
                font = FONT_BOLD if f == menu_model.active_tab else FONT_NORMAL
                window[key].update(font=font)

        for event, values in window.event_iter():
            if event == eg.WIN_CLOSED:
                break
            elif event == "new_task:enter":
                task = values.get("new_task", "").strip()
                if task:
                    todo_model.add(task)
                    window["new_task"].update("")
                    todo_list.refresh()
            elif event == "tab_all":
                menu_model.active_tab = TabFilter.ALL
                update_tabs(); todo_list.refresh()
            elif event == "tab_active":
                menu_model.active_tab = TabFilter.ACTIVE
                update_tabs(); todo_list.refresh()
            elif event == "tab_completed":
                menu_model.active_tab = TabFilter.COMPLETED
                update_tabs(); todo_list.refresh()


if __name__ == "__main__":
    main()
