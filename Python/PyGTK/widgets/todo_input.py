import gi
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk
from typing import Callable
from theme import Theme, set_color, rounded_rect


class TodoInput(Gtk.Overlay):
    def __init__(self, on_submit: Callable[[str], None]):
        super().__init__()
        self._on_submit = on_submit
        self.set_size_request(-1, Theme.ITEM_H)

        self._entry = Gtk.Entry()
        self._entry.set_placeholder_text("Add Task")
        self._entry.get_style_context().add_class("todo-entry")
        self._entry.connect("activate", self._handle_submit)
        self.add(self._entry)

        self._border = Gtk.DrawingArea()
        self._border.set_can_focus(False)
        self._border.connect("draw", self._draw_border)
        self.add_overlay(self._border)
        self.set_overlay_pass_through(self._border, True)

        self._entry.connect("focus-in-event",  lambda *_: (self._border.queue_draw(), False))
        self._entry.connect("focus-out-event", lambda *_: (self._border.queue_draw(), False))

    def _handle_submit(self, _entry):
        text = self._entry.get_text().strip()
        if text:
            self._on_submit(text)
            self._entry.set_text("")

    def _draw_border(self, _widget, cr):
        if not self._entry.has_focus():
            return
        w = self.get_allocated_width()
        h = self.get_allocated_height()
        set_color(cr, Theme.ACCENT_C)
        cr.set_line_width(1)
        rounded_rect(cr, 0.5, 0.5, w - 1, h - 1, 4)
        cr.stroke()