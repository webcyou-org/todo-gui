"""TodoInput widget."""
from typing import Callable

import wx

from theme import C_INPUT, C_WHITE, FONT_SZ, ITEM_H, font


def make_input(parent: wx.Window, on_add: Callable[[str], None]) -> wx.TextCtrl:
    task_input = wx.TextCtrl(
        parent, style=wx.TE_PROCESS_ENTER | wx.BORDER_NONE,
        size=(-1, ITEM_H),
    )
    task_input.SetHint("Add Task")
    task_input.SetBackgroundColour(C_INPUT)
    task_input.SetForegroundColour(C_WHITE)
    task_input.SetFont(font(FONT_SZ))

    def on_enter(_event: wx.CommandEvent) -> None:
        task = task_input.GetValue().strip()
        if task:
            task_input.SetValue("")
            on_add(task)

    task_input.Bind(wx.EVT_TEXT_ENTER, on_enter)
    return task_input