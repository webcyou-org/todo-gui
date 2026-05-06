#!/usr/bin/env python3
import wx

from data import MenuModel, TodoModel
from theme import C_BG, C_WHITE, font
from widgets.tabs import TabMenuPanel
from widgets.todo_input import make_input
from widgets.todo_item import TodoListPanel


class MainFrame(wx.Frame):
    def __init__(self) -> None:
        super().__init__(None, title="ToDo", size=(800, 600),
                         style=wx.DEFAULT_FRAME_STYLE & ~wx.RESIZE_BORDER & ~wx.MAXIMIZE_BOX)
        self.SetBackgroundColour(C_BG)

        todo_model = TodoModel()
        menu_model = MenuModel()

        root = wx.Panel(self)
        root.SetBackgroundColour(C_BG)
        sizer = wx.BoxSizer(wx.VERTICAL)

        # Title
        title = wx.StaticText(root, label="ToDo")
        title.SetFont(font(size=16, bold=True))
        title.SetForegroundColour(C_WHITE)
        title.SetBackgroundColour(C_BG)
        sizer.Add(title, 0, wx.LEFT | wx.RIGHT | wx.TOP, 24)
        sizer.Add((0, 14))

        # Todo list (defined early — passed to tab switch callback)
        todo_list = TodoListPanel(root, todo_model, menu_model)

        # Input
        task_input = make_input(root, lambda task: (todo_model.add_todo(task), todo_list.refresh()))
        sizer.Add(task_input, 0, wx.EXPAND | wx.LEFT | wx.RIGHT, 24)
        sizer.Add((0, 14))

        # Tabs
        tabs = TabMenuPanel(root, menu_model, on_switch=todo_list.refresh)
        sizer.Add(tabs, 0, wx.EXPAND | wx.LEFT | wx.RIGHT, 24)
        sizer.Add((0, 3))

        # List
        sizer.Add(todo_list, 1, wx.EXPAND | wx.LEFT | wx.RIGHT | wx.BOTTOM, 24)

        root.SetSizer(sizer)
        todo_list.refresh()
        self.Show()


def main() -> None:
    app = wx.App(False)
    MainFrame()
    app.MainLoop()


if __name__ == "__main__":
    main()