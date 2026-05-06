"""TodoInput widget."""
from typing import Callable

import toga
from toga.style import Pack

from theme import C_INPUT, C_WHITE, FONT_SZ, ITEM_H


def make_input(on_add: Callable[[str], None]) -> toga.TextInput:
    def on_confirm(widget: toga.TextInput) -> None:
        task = widget.value.strip()
        if task:
            widget.value = ""
            on_add(task)

    return toga.TextInput(
        placeholder="Add Task",
        style=Pack(
            height=ITEM_H,
            flex=1,
            background_color=C_INPUT,
            color=C_WHITE,
            font_size=FONT_SZ,
            margin_bottom=14,
        ),
        on_confirm=on_confirm,
    )