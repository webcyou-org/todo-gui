"""TodoItem and TodoListPanel widgets."""
from typing import Callable

import wx

from data import Todo, TodoModel, MenuModel
from theme import (
    C_ACCENT, C_BG, C_CB_BDR, C_MUTED, C_SURFACE, C_TEXT, C_WHITE,
    CB_MR, CB_PAD_L, CB_SIZE, FONT_SZ, ITEM_H, ITEM_MB, font,
)

_TX = CB_PAD_L + CB_SIZE + CB_MR  # text left edge = 44


class TodoItem(wx.Panel):
    def __init__(self, parent: wx.Window, todo: Todo,
                 on_toggle: Callable[[int], None]) -> None:
        super().__init__(parent, size=(-1, ITEM_H))
        self._todo = todo
        self._on_toggle = on_toggle
        self.SetBackgroundColour(C_BG)
        self.SetMinSize((-1, ITEM_H))
        self.Bind(wx.EVT_PAINT, self._on_paint)
        self.Bind(wx.EVT_LEFT_DOWN, self._on_click)
        self.Bind(wx.EVT_SIZE, lambda _: self.Refresh())

    def _on_paint(self, _event: wx.PaintEvent) -> None:
        dc = wx.AutoBufferedPaintDC(self)
        dc.SetBackground(wx.Brush(C_BG))
        dc.Clear()
        gc = wx.GraphicsContext.Create(dc)
        w, h = self.GetSize()
        cy = h / 2

        # Rounded-rect surface
        gc.SetBrush(gc.CreateBrush(wx.Brush(C_SURFACE)))
        gc.SetPen(wx.TRANSPARENT_PEN)
        gc.DrawRoundedRectangle(0, 0, w, h, 4)

        # Circular checkbox
        cx = CB_PAD_L + CB_SIZE / 2
        r = CB_SIZE / 2 - 1
        if self._todo.is_completed:
            gc.SetBrush(gc.CreateBrush(wx.Brush(C_ACCENT)))
            gc.SetPen(wx.TRANSPARENT_PEN)
            gc.DrawEllipse(cx - r, cy - r, r * 2, r * 2)
            pen = gc.CreatePen(wx.GraphicsPenInfo(C_WHITE).Width(1.5))
            gc.SetPen(pen)
            path = gc.CreatePath()
            path.MoveToPoint(cx - 4, cy)
            path.AddLineToPoint(cx - 1, cy + 3)
            path.AddLineToPoint(cx + 4, cy - 3)
            gc.StrokePath(path)
        else:
            pen = gc.CreatePen(wx.GraphicsPenInfo(C_CB_BDR).Width(2))
            gc.SetPen(pen)
            gc.SetBrush(wx.TRANSPARENT_BRUSH)
            gc.DrawEllipse(cx - r, cy - r, r * 2, r * 2)

        # Task label
        text_color = C_MUTED if self._todo.is_completed else C_TEXT
        gc.SetFont(gc.CreateFont(font(FONT_SZ), text_color))
        _, th = gc.GetTextExtent(self._todo.task)
        gc.DrawText(self._todo.task, _TX, cy - th / 2)

        # Strikethrough
        if self._todo.is_completed:
            tw, _ = gc.GetTextExtent(self._todo.task)
            gc.SetPen(gc.CreatePen(wx.GraphicsPenInfo(C_MUTED).Width(1)))
            gc.StrokeLine(_TX, cy, _TX + tw, cy)

    def _on_click(self, event: wx.MouseEvent) -> None:
        if event.GetX() <= CB_PAD_L + CB_SIZE + 10:
            self._on_toggle(self._todo.id)


class TodoListPanel(wx.ScrolledWindow):
    def __init__(self, parent: wx.Window, todo_model: TodoModel,
                 menu_model: MenuModel) -> None:
        super().__init__(parent, style=wx.VSCROLL)
        self._todo_model = todo_model
        self._menu_model = menu_model
        self.SetBackgroundColour(C_BG)
        self.SetScrollRate(0, 10)
        self._sizer = wx.BoxSizer(wx.VERTICAL)
        self.SetSizer(self._sizer)

    def refresh(self) -> None:
        self._sizer.Clear(True)
        for todo in self._todo_model.get_filtered_todos(self._menu_model.get_active_tab()):
            item = TodoItem(self, todo, self._toggle)
            self._sizer.Add(item, 0, wx.EXPAND | wx.BOTTOM, ITEM_MB)
        self._sizer.Layout()
        self.FitInside()
        self.Refresh()

    def _toggle(self, todo_id: int) -> None:
        self._todo_model.change_completed(todo_id)
        self.refresh()