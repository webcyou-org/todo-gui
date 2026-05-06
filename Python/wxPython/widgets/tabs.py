"""TabMenuPanel — custom-drawn tab bar."""
from typing import Callable, List, Tuple

import wx

from data import MenuModel, TabFilter
from theme import C_BG, C_TEXT, FONT_SZ, font

_TAB_DEFS: List[Tuple[TabFilter, str]] = [
    (TabFilter.ALL,       "All"),
    (TabFilter.ACTIVE,    "Active"),
    (TabFilter.COMPLETED, "Completed"),
]


class TabMenuPanel(wx.Panel):
    def __init__(self, parent: wx.Window, menu_model: MenuModel,
                 on_switch: Callable) -> None:
        super().__init__(parent, size=(-1, 28))
        self._model = menu_model
        self._on_switch = on_switch
        self._boundaries: List[Tuple[float, float, TabFilter]] = []
        self.SetBackgroundColour(C_BG)
        self.Bind(wx.EVT_PAINT, self._on_paint)
        self.Bind(wx.EVT_LEFT_DOWN, self._on_click)

    def _on_paint(self, _event: wx.PaintEvent) -> None:
        dc = wx.AutoBufferedPaintDC(self)
        dc.SetBackground(wx.Brush(C_BG))
        dc.Clear()
        gc = wx.GraphicsContext.Create(dc)
        self._boundaries.clear()
        x, pad = 0.0, 8
        active = self._model.get_active_tab()
        h = self.GetSize().height

        for tf, label in _TAB_DEFS:
            f = font(FONT_SZ, bold=(tf == active))
            gc.SetFont(gc.CreateFont(f, C_TEXT))
            tw, th = gc.GetTextExtent(label)
            tab_w = tw + pad * 2
            self._boundaries.append((x, x + tab_w, tf))
            gc.DrawText(label, x + pad, (h - th) / 2)
            x += tab_w

    def _on_click(self, event: wx.MouseEvent) -> None:
        px = event.GetX()
        for x_start, x_end, tf in self._boundaries:
            if x_start <= px <= x_end:
                self._model.set_active_tab(tf)
                self.Refresh()
                self._on_switch()
                break