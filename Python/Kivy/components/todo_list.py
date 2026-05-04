from typing import Callable

from kivy.metrics import dp
from kivy.uix.scrollview import ScrollView
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.widget import Widget
from kivy.uix.label import Label
from kivy.graphics import Color, RoundedRectangle, Ellipse, Line
from kivy.input.motionevent import MotionEvent

from data import MenuModel, Todo, TodoModel, TabFilter
from theme import (
    C_BG, C_SURFACE, C_TEXT, C_MUTED, C_ACCENT, C_WHITE, C_CB_BORDER,
    FONT_SIZE_NORMAL, FONT_NAME,
)


_CB_SIZE = dp(16)
_ROW_H   = dp(40)


class _CircleCheckbox(Widget):
    def __init__(self, is_completed: bool, **kwargs):
        super().__init__(size_hint=(None, None), size=(_CB_SIZE, _CB_SIZE), **kwargs)
        self.is_completed = is_completed
        self.bind(pos=self._draw, size=self._draw)

    def _draw(self, *_):
        self.canvas.clear()
        s = self.width  # actual rendered size (dp-scaled)
        with self.canvas:
            if self.is_completed:
                Color(*C_ACCENT)
                Ellipse(pos=self.pos, size=self.size)
                Color(*C_WHITE)
                Line(
                    points=[
                        self.x + s * 0.25, self.y + s * 0.50,
                        self.x + s * 0.44, self.y + s * 0.31,
                        self.x + s * 0.75, self.y + s * 0.69,
                    ],
                    width=dp(1.5),
                    cap='round',
                    joint='round',
                )
            else:
                Color(*C_CB_BORDER)
                Line(ellipse=(*self.pos, *self.size), width=dp(1.5))


class _TodoRow(BoxLayout):
    def __init__(self, todo: Todo, on_toggle: Callable[[Todo], None], **kwargs):
        super().__init__(
            orientation='horizontal',
            size_hint=(1, None),
            height=_ROW_H,
            padding=[dp(10), 0],
            spacing=dp(8),
            **kwargs,
        )
        self._todo = todo
        self._on_toggle = on_toggle
        self._build()
        self.bind(pos=self._draw_bg, size=self._draw_bg)

    def _draw_bg(self, *_):
        self.canvas.before.clear()
        with self.canvas.before:
            Color(*C_SURFACE)
            RoundedRectangle(pos=self.pos, size=self.size, radius=[4])

    def _build(self):
        self._cb = _CircleCheckbox(
            is_completed=self._todo.is_completed,
            pos_hint={'center_y': 0.5},
        )
        self.add_widget(self._cb)

        text = self._make_label_text()
        self._label = Label(
            text=text,
            markup=True,
            font_name=FONT_NAME,
            font_size=FONT_SIZE_NORMAL,
            color=C_MUTED if self._todo.is_completed else C_TEXT,
            halign='left',
            valign='middle',
            size_hint=(1, 1),
        )
        # text_size must include height for valign='middle' to work
        self._label.bind(size=lambda w, _: setattr(w, 'text_size', (w.width, w.height)))
        self.add_widget(self._label)

    def _make_label_text(self) -> str:
        t = self._todo.task
        return f'[s]{t}[/s]' if self._todo.is_completed else t

    def on_touch_down(self, touch: MotionEvent):
        if self.collide_point(*touch.pos):
            self._on_toggle(self._todo)
            return True
        return super().on_touch_down(touch)


class TodoList(ScrollView):
    def __init__(self, todo_model: TodoModel, menu_model: MenuModel, **kwargs):
        super().__init__(
            do_scroll_x=False,
            size_hint=(1, 1),
            **kwargs,
        )
        self._todo_model = todo_model
        self._menu_model = menu_model

        self._inner = BoxLayout(
            orientation='vertical',
            size_hint_y=None,
            spacing=5,
        )
        self._inner.bind(minimum_height=self._inner.setter('height'))
        self.add_widget(self._inner)
        self.refresh()

    def refresh(self):
        self._inner.clear_widgets()
        todos = self._todo_model.get_filtered_todos(self._menu_model.get_active_tab())
        for todo in todos:
            self._inner.add_widget(_TodoRow(todo=todo, on_toggle=self._on_toggle))

    def _on_toggle(self, todo: Todo):
        self._todo_model.change_completed(todo)
        self.refresh()