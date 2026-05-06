import gi
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk, Gdk, GLib
import subprocess

from data import TodoModel, MenuModel, TabFilter
from theme import Theme
from widgets.todo_input import TodoInput
from widgets.tab_menu import TabMenu
from widgets.todo_list import TodoList


class TodoApp(Gtk.Window):
    def __init__(self):
        super().__init__(title="ToDo")
        self.set_default_size(800, 600)
        self.set_resizable(False)
        self.connect("destroy", Gtk.main_quit)

        css = Gtk.CssProvider()
        css.load_from_data(Theme.CSS)
        Gtk.StyleContext.add_provider_for_screen(
            Gdk.Screen.get_default(), css,
            Gtk.STYLE_PROVIDER_PRIORITY_APPLICATION)

        self._todo_model = TodoModel()
        self._menu_model = MenuModel()

        outer = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=0)
        outer.set_margin_start(24)
        outer.set_margin_end(24)
        outer.set_margin_top(10)
        outer.set_margin_bottom(10)
        self.add(outer)

        title = Gtk.Label(label="ToDo")
        title.set_halign(Gtk.Align.START)
        title.get_style_context().add_class("title")
        outer.pack_start(title, False, False, 0)
        outer.pack_start(Gtk.Box(), False, False, 7)

        self._input = TodoInput(self._on_add_todo)
        outer.pack_start(self._input, False, False, 0)
        outer.pack_start(Gtk.Box(), False, False, 7)

        self._tab_menu = TabMenu(self._on_tab_change)
        outer.pack_start(self._tab_menu, False, False, 0)
        outer.pack_start(Gtk.Box(), False, False, 3)

        self._todo_list = TodoList(self._on_toggle)
        outer.pack_start(self._todo_list, True, True, 0)

        self._refresh_list()

    def _refresh_list(self):
        self._todo_list.refresh(self._todo_model.filtered(self._menu_model.active_tab))

    def _on_add_todo(self, task: str):
        self._todo_model.add_todo(task)
        self._refresh_list()

    def _on_tab_change(self, f: TabFilter):
        self._menu_model.active_tab = f
        self._tab_menu.set_active(f)
        self._refresh_list()

    def _on_toggle(self, id: int):
        self._todo_model.toggle(id)
        self._refresh_list()


def _focus_window():
    subprocess.Popen([
        "osascript", "-e",
        'tell application "System Events" to tell process "python3" to set frontmost to true'
    ])
    return False


def main():
    app = TodoApp()
    app.show_all()
    GLib.idle_add(app.present)
    GLib.timeout_add(300, _focus_window)
    Gtk.main()


if __name__ == "__main__":
    main()