from typing import Callable

from kivy.metrics import dp
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.textinput import TextInput
from kivy.graphics import Color, RoundedRectangle, Line

from theme import C_INPUT, C_MUTED, C_WHITE, C_ACCENT, FONT_SIZE_NORMAL, FONT_NAME

_HEIGHT = dp(40)


class TodoInput(BoxLayout):
    def __init__(self, on_add: Callable[[str], None], **kwargs):
        super().__init__(size_hint=(1, None), height=_HEIGHT, **kwargs)
        self._on_add = on_add

        # All canvas instructions must be created INSIDE the with block
        with self.canvas.before:
            self._bg_color     = Color(*C_INPUT)
            self._bg_rect      = RoundedRectangle(pos=self.pos, size=self.size, radius=[dp(4)])
            self._border_color = Color(0, 0, 0, 0)
            self._border_line  = Line(
                rounded_rectangle=(self.x, self.y, self.width, self.height, dp(4)),
                width=1,
            )

        self.bind(pos=self._update_bg, size=self._update_bg)

        self._ti = TextInput(
            hint_text='Add Task',
            hint_text_color=C_MUTED,
            foreground_color=C_WHITE,
            background_normal='',
            background_active='',
            background_color=(0, 0, 0, 0),
            cursor_color=C_WHITE,
            font_name=FONT_NAME,
            font_size=FONT_SIZE_NORMAL,
            multiline=False,
            padding=[dp(10), dp(11), dp(10), dp(11)],
            size_hint=(1, 1),
        )
        self._ti.bind(
            on_text_validate=self._on_enter,
            focus=self._on_focus,
        )
        self.add_widget(self._ti)

    def _update_bg(self, *_):
        self._bg_rect.pos  = self.pos
        self._bg_rect.size = self.size
        self._border_line.rounded_rectangle = (
            self.x + 0.5, self.y + 0.5,
            self.width - 1, self.height - 1,
            dp(4),
        )

    def _on_focus(self, _, focused: bool):
        self._border_color.rgba = C_ACCENT if focused else (0, 0, 0, 0)

    def _on_enter(self, instance):
        task = instance.text.strip()
        if task:
            self._on_add(task)
            instance.text = ''