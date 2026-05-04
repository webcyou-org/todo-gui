from typing import Callable

from kivy.metrics import dp
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.label import Label
from kivy.input.motionevent import MotionEvent

from data import MenuModel, TabFilter
from theme import C_TEXT, FONT_SIZE_NORMAL, FONT_NAME


class _TabLabel(Label):
    def __init__(self, tab: TabFilter, active: bool,
                 on_change: Callable[[TabFilter], None], **kwargs):
        super().__init__(
            text=tab.value,
            font_name=FONT_NAME,
            font_size=FONT_SIZE_NORMAL,
            bold=active,
            color=C_TEXT,
            size_hint=(None, 1),
            width=self._text_width(tab.value, active),
            halign='center',
            **kwargs,
        )
        self._tab = tab
        self._on_change = on_change

    @staticmethod
    def _text_width(text: str, bold: bool) -> int:
        base = {'All': 40, 'Active': 72, 'Completed': 112}
        return dp(base.get(text, len(text) * 10) + 16)

    def on_touch_down(self, touch: MotionEvent):
        if self.collide_point(*touch.pos):
            self._on_change(self._tab)
            return True
        return super().on_touch_down(touch)


class TabMenu(BoxLayout):
    def __init__(self, menu_model: MenuModel,
                 on_change: Callable[[TabFilter], None], **kwargs):
        super().__init__(
            orientation='horizontal',
            size_hint=(1, None),
            height=dp(32),
            spacing=0,
            **kwargs,
        )
        self._menu_model = menu_model
        self._on_change = on_change
        self.refresh()

    def refresh(self):
        self.clear_widgets()
        active = self._menu_model.get_active_tab()
        for tab in self._menu_model.get_tab_list():
            self.add_widget(_TabLabel(
                tab=tab,
                active=(tab == active),
                on_change=self._on_change,
            ))
        # spacer
        from kivy.uix.widget import Widget
        self.add_widget(Widget(size_hint_x=1))
