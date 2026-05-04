from kivy.config import Config
Config.set('graphics', 'width', '800')
Config.set('graphics', 'height', '600')
Config.set('graphics', 'resizable', '0')
Config.set('kivy', 'keyboard_mode', 'system')
Config.set('input', 'mouse', 'mouse,disable_multitouch')

from kivy.app import App
from kivy.core.window import Window
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.label import Label

from theme import C_BG, C_WHITE, FONT_SIZE_TITLE, FONT_NAME
from data import TodoModel, MenuModel, TabFilter
from components.todo_input import TodoInput
from components.tabs import TabMenu
from components.todo_list import TodoList


class RootWidget(BoxLayout):
    def __init__(self, todo_model: TodoModel, menu_model: MenuModel, **kwargs):
        super().__init__(**kwargs)
        self.orientation = 'vertical'
        self.padding = [24, 10]
        self.spacing = 10
        self._todo_model = todo_model
        self._menu_model = menu_model
        self._build()

    def _build(self):
        title = Label(
            text='ToDo',
            font_name=FONT_NAME,
            font_size=FONT_SIZE_TITLE,
            bold=True,
            color=C_WHITE,
            size_hint=(1, None),
            height=30,
            halign='left',
        )
        title.bind(size=lambda w, _: setattr(w, 'text_size', (w.width, None)))
        self.add_widget(title)

        self.add_widget(TodoInput(on_add=self._on_add))
        self._tab_menu = TabMenu(
            menu_model=self._menu_model,
            on_change=self._on_tab_change,
        )
        self.add_widget(self._tab_menu)
        self._todo_list = TodoList(
            todo_model=self._todo_model,
            menu_model=self._menu_model,
        )
        self.add_widget(self._todo_list)

    def _on_add(self, task: str):
        self._todo_model.add_todo(task)
        self._todo_list.refresh()

    def _on_tab_change(self, tab: TabFilter):
        self._menu_model.set_active_tab(tab)
        self._tab_menu.refresh()
        self._todo_list.refresh()


class TodoApp(App):
    def build(self):
        Window.clearcolor = C_BG
        todo_model = TodoModel()
        menu_model = MenuModel()
        return RootWidget(todo_model=todo_model, menu_model=menu_model)


if __name__ == '__main__':
    TodoApp().run()