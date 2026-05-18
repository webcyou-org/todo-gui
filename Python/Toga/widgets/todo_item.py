"""Canvas-based TodoItem widget."""
from typing import Callable

import toga
from toga.constants import Baseline
from toga.fonts import Font
from toga.style import Pack

from data import Todo, TodoModel
from theme import (
    C_ACCENT, C_CB_BDR, C_MUTED, C_SURFACE, C_TEXT, C_WHITE,
    CB_MR, CB_PAD_L, CB_SIZE, FONT_SZ, ITEM_H, ITEM_MB,
)

_FONT = Font("system", FONT_SZ)
_TX   = CB_PAD_L + CB_SIZE + CB_MR  # text left edge = 44


def _draw(canvas: toga.Canvas, todo: Todo) -> None:
    # Clear previous drawing commands directly on the state list
    canvas.root_state.drawing_actions.clear()

    cy = ITEM_H // 2                # 17 — vertical centre
    cx = CB_PAD_L + CB_SIZE // 2    # 18 — checkbox centre x
    r  = CB_SIZE // 2 - 1           #  7 — checkbox radius

    if todo.is_completed:
        # Outlined circle in CB border color
        with canvas.stroke(color=C_CB_BDR, line_width=1.5):
            canvas.arc(cx, cy, r)
        # Checkmark ✓ in accent color
        with canvas.stroke(color=C_ACCENT, line_width=1.5):
            canvas.move_to(cx - 4, cy)
            canvas.line_to(cx - 1, cy + 3)
            canvas.line_to(cx + 4, cy - 3)
    else:
        # Outlined circle
        with canvas.stroke(color=C_CB_BDR, line_width=2):
            canvas.arc(cx, cy, r)

    # Task text
    text_color = C_MUTED if todo.is_completed else C_TEXT
    with canvas.fill(color=text_color):
        canvas.write_text(todo.task, _TX, cy, font=_FONT, baseline=Baseline.MIDDLE)

    # Strikethrough line for completed tasks
    if todo.is_completed:
        try:
            text_w, _ = canvas.measure_text(todo.task, font=_FONT)
        except Exception:
            text_w = len(todo.task) * 8
        with canvas.stroke(color=C_MUTED, line_width=1):
            canvas.move_to(_TX, cy)
            canvas.line_to(_TX + text_w, cy)


def make_todo_item(todo: Todo, model: TodoModel, refresh_cb: Callable) -> toga.Canvas:
    def on_resize(w: toga.Canvas, width: float, height: float, **_) -> None:
        _draw(w, todo)

    canvas = toga.Canvas(
        style=Pack(
            height=ITEM_H,
            flex=1,
            background_color=C_SURFACE,
            margin_bottom=ITEM_MB,
        ),
        on_resize=on_resize,
        on_press=lambda w, x, y, **kw: _on_press(todo, model, refresh_cb, x),
    )
    _draw(canvas, todo)
    return canvas


def _on_press(todo: Todo, model: TodoModel, refresh_cb: Callable, x: float) -> None:
    if x <= CB_PAD_L + CB_SIZE + 10:
        model.change_completed(todo.id)
        refresh_cb()
