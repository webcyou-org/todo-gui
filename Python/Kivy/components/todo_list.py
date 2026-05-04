from typing import Callable

from kivy.uix.scrollview import ScrollView
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.widget import Widget
from kivy.uix.label import Label
from kivy.graphics import Color, RoundedRectangle, Ellipse, Line
from kivy.input.motionevent import MotionEvent

from data import MenuModel, Todo, TodoModel, TabFilter
from theme import (
    C_BG, C_SURFACE, C_TEXT, C_MUTED, C_ACCENT, C_WHITE, C_CB_BORDER,
    FONT_SIZE_NORMAL,
)


class _CircleCheckbox(Widget):
    def __init__(self, is_completed: bool, **kwargs):
        super().__init__(size_hint=(None, None), size=(16, 16), **kwargs)
        self.is_completed = is_completed
        self.bind(pos=self._draw, size=self._draw)

    def _draw(self, *_):
        self.canvas.clear()
        with self.canvas:
            if self.is_completed:
                Color(*C_ACCENT)
                Ellipse(pos=self.pos, size=self.size)
                Color(*C_WHITE)
                cx, cy = self.center_x, self.center_y
                Line(
                    points=[
                        self.x + 4,  self.y + 8,
                        self.x + 7,  self.y + 5,
                        self.x + 12, self.y + 11,
                    ],
                    width=1.5,
                    cap='round',
                    joint='round',
                )
            else:
                Color(*C_CB_BORDER)
                Line(ellipse=(*self.pos, *self.size), width=1.5)


class _TodoRow(BoxLayout):
    def __init__(self, todo: Todo, on_toggle: Callable[[Todo], None], **kwargs):
        super().__init__(
            orientation='horizontal',
            size_hint=(1, None),
            height=35,
            padding=[10, 0],
            spacing=8,
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
        self._cb = _CircleCheckbox(is_completed=self._todo.is_completed)
        # Wrap checkbox in a container to vertically center it
        cb_box = BoxLayout(size_hint=(None, 1), width=16)
        cb_box.add_widget(self._cb)
        self.add_widget(cb_box)

        text = self._make_label_text()
        self._label = Label(
            text=text,
            markup=True,
            font_size=FONT_SIZE_NORMAL,
            color=C_MUTED if self._todo.is_completed else C_TEXT,
            halign='left',
            valign='middle',
            size_hint=(1, 1),
        )
        self._label.bind(size=lambda w, _: setattr(w, 'text_size', (w.width, None)))
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