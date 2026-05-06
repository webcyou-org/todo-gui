"""TabMenu widget — Canvas-based for full color control."""
from typing import Callable, List, Tuple

import toga
from toga.constants import Baseline
from toga.fonts import Font
from toga.style import Pack
from toga.style.pack import BOLD, NORMAL

from data import MenuModel, TabFilter
from theme import C_BG, C_TEXT, FONT_SZ

_TABS: List[Tuple[TabFilter, str]] = [
    (TabFilter.ALL,       "All"),
    (TabFilter.ACTIVE,    "Active"),
    (TabFilter.COMPLETED, "Completed"),
]
_FONT_BOLD   = Font("system", FONT_SZ, weight=BOLD)
_FONT_NORMAL = Font("system", FONT_SZ, weight=NORMAL)
_PAD = 8   # horizontal padding per tab side
_H   = 28  # tab bar height


def make_tabs(menu_model: MenuModel, on_tab_changed: Callable) -> toga.Canvas:
    # Store (x_start, x_end, TabFilter) for hit-testing on press
    _boundaries: List[Tuple[float, float, TabFilter]] = []

    def draw(canvas: toga.Canvas, **_) -> None:
        canvas.root_state.drawing_actions.clear()
        _boundaries.clear()
        x: float = 0.0
        active = menu_model.get_active_tab()

        for tab_filter, label in _TABS:
            font = _FONT_BOLD if tab_filter == active else _FONT_NORMAL
            try:
                text_w, _ = canvas.measure_text(label, font=font)
            except Exception:
                text_w = float(len(label) * 8)

            tab_w = text_w + _PAD * 2
            _boundaries.append((x, x + tab_w, tab_filter))

            with canvas.fill(color=C_TEXT):
                canvas.write_text(label, x + _PAD, _H // 2, font=font,
                                  baseline=Baseline.MIDDLE)
            x += tab_w

    def handle_press(canvas: toga.Canvas, px: float, py: float, **_) -> None:
        for x_start, x_end, tf in _boundaries:
            if x_start <= px <= x_end:
                menu_model.set_active_tab(tf)
                draw(canvas)
                on_tab_changed()
                break

    tab_canvas = toga.Canvas(
        style=Pack(
            height=_H,
            flex=1,
            background_color=C_BG,
            margin_bottom=3,
        ),
        on_resize=lambda w, width, height, **kw: draw(w),
        on_press=handle_press,
    )
    draw(tab_canvas)
    return tab_canvas