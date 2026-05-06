#!/opt/homebrew/bin/python3.9
import sys, os
sys.path.insert(0, os.path.dirname(__file__))

import TkEasyGUI as eg
import tkinter as tk

from data import TodoModel, MenuModel, TabFilter
from theme import Theme, FONT_TITLE, FONT_NORMAL, FONT_BOLD
from widgets.todo_list import TodoListWidget


def main():
    todo_model = TodoModel()
    menu_model = MenuModel()

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
            eg.Button("All",       key="tab_all",       font=FONT_BOLD,   pad=((0,0),(0,3)), button_color=(Theme.TEXT, Theme.BG)),
            eg.Button("Active",    key="tab_active",    font=FONT_NORMAL, pad=((0,0),(0,3)), button_color=(Theme.TEXT, Theme.BG)),
            eg.Button("Completed", key="tab_completed", font=FONT_NORMAL, pad=((0,0),(0,3)), button_color=(Theme.TEXT, Theme.BG)),
        ],
        [eg.Canvas(key="todo_canvas", background_color=Theme.BG,
                   size=(752, 460), expand_x=True, expand_y=True)],
    ]

    with eg.Window(
        "ToDo",
        layout,
        size=(800, 600),
        background_color=Theme.BG,
        margins=(24, 10),
        resizable=False,
    ) as window:
        # Input styling
        input_widget: tk.Entry = window["new_task"].widget
        input_widget.configure(
            relief="flat",
            highlightthickness=1,
            highlightbackground=Theme.INPUT,
            highlightcolor=Theme.ACCENT,
            insertbackground=Theme.WHITE,
        )

        # Todo list setup
        canvas: tk.Canvas = window["todo_canvas"].widget
        scrollbar = tk.Scrollbar(canvas.master, orient="vertical")
        scrollbar.pack(side="right", fill="y")

        todo_list = TodoListWidget(canvas, todo_model, lambda: menu_model.active_tab)
        todo_list.attach_scrollbar(scrollbar)
        todo_list.refresh()

        def update_tabs():
            for f, key in [(TabFilter.ALL, "tab_all"), (TabFilter.ACTIVE, "tab_active"),
                           (TabFilter.COMPLETED, "tab_completed")]:
                window[key].update(font=FONT_BOLD if f == menu_model.active_tab else FONT_NORMAL)

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