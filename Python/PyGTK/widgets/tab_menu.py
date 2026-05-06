import gi
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk
from typing import Callable, List
from data import TabFilter
from theme import Theme

TAB_LABELS = [
    (TabFilter.ALL,       "All"),
    (TabFilter.ACTIVE,    "Active"),
    (TabFilter.COMPLETED, "Completed"),
]


class TabMenu(Gtk.Box):
    def __init__(self, on_change: Callable[[TabFilter], None]):
        super().__init__(orientation=Gtk.Orientation.HORIZONTAL, spacing=0)
        self._on_change = on_change
        self._buttons: List = []

        for f, label in TAB_LABELS:
            btn = Gtk.Button(label=label)
            btn.get_style_context().add_class("tab-btn")
            btn.connect("clicked", lambda _b, fv=f: self._click(fv))
            self._buttons.append((f, btn))
            self.pack_start(btn, False, False, 0)

        self.set_active(TabFilter.ALL)

    def set_active(self, active: TabFilter):
        for f, btn in self._buttons:
            ctx = btn.get_style_context()
            if f == active:
                ctx.add_class("tab-btn-active")
            else:
                ctx.remove_class("tab-btn-active")

    def _click(self, f: TabFilter):
        self.set_active(f)
        self._on_change(f)