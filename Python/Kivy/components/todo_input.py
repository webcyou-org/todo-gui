from typing import Callable

from kivy.uix.textinput import TextInput
from kivy.graphics import Color, RoundedRectangle, Line

from theme import C_INPUT, C_MUTED, C_WHITE, C_ACCENT, FONT_SIZE_NORMAL


class TodoInput(TextInput):
    def __init__(self, on_add: Callable[[str], None], **kwargs):
        super().__init__(
            hint_text='Add Task',
            hint_text_color=C_MUTED,
            foreground_color=C_WHITE,
            background_color=(0, 0, 0, 0),  # transparent — drawn manually
            cursor_color=C_WHITE,
            font_size=FONT_SIZE_NORMAL,
            multiline=False,
            padding=[10, 8],
            size_hint=(1, None),
            height=35,
            **kwargs,
        )
        self._on_add = on_add
        self._focused = False
        self.bind(pos=self._draw_bg, size=self._draw_bg, focus=self._on_focus)

    def _draw_bg(self, *_):
        self.canvas.before.clear()
        with self.canvas.before:
            Color(*C_INPUT)
            RoundedRectangle(pos=self.pos, size=self.size, radius=[4])
            if self._focused:
                Color(*C_ACCENT)
                Line(
                    rounded_rectangle=(
                        self.x + 0.5, self.y + 0.5,
                        self.width - 1, self.height - 1,
                        4,
                    ),
                    width=1,
                )

    def _on_focus(self, _, focused: bool):
        self._focused = focused
        self._draw_bg()

    def keyboard_on_key_down(self, window, keycode, text, modifiers):
        if keycode[1] == 'enter':
            task = self.text.strip()
            if task:
                self._on_add(task)
                self.text = ''
            return True
        return super().keyboard_on_key_down(window, keycode, text, modifiers)