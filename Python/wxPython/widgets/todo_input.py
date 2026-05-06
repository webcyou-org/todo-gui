"""TodoInput widget — Panel wrapper for vertical centering."""
from typing import Callable

import wx

from theme import C_BG, C_INPUT, C_WHITE, FONT_SZ, ITEM_H, font


class TodoInputPanel(wx.Panel):
    """Panel that contains a vertically centered TextCtrl with dark styling."""

    def __init__(self, parent: wx.Window, on_add: Callable[[str], None]) -> None:
        super().__init__(parent, size=(-1, ITEM_H))
        self.SetBackgroundColour(C_INPUT)
        self.SetMinSize((-1, ITEM_H))

        self._ctrl = wx.TextCtrl(self, style=wx.TE_PROCESS_ENTER | wx.BORDER_NONE)
        self._ctrl.SetBackgroundColour(C_INPUT)
        self._ctrl.SetForegroundColour(C_WHITE)
        self._ctrl.SetFont(font(FONT_SZ))
        self._ctrl.SetHint("Add Task")

        # Stretch spacers push ctrl to the vertical centre
        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.AddStretchSpacer(1)
        sizer.Add(self._ctrl, 0, wx.EXPAND | wx.LEFT | wx.RIGHT, 16)
        sizer.AddStretchSpacer(1)
        self.SetSizer(sizer)

        self._ctrl.Bind(wx.EVT_TEXT_ENTER, self._on_enter)
        self._on_add = on_add

    def _on_enter(self, _event: wx.CommandEvent) -> None:
        task = self._ctrl.GetValue().strip()
        if task:
            self._ctrl.SetValue("")
            self._on_add(task)


def make_input(parent: wx.Window, on_add: Callable[[str], None]) -> TodoInputPanel:
    return TodoInputPanel(parent, on_add)