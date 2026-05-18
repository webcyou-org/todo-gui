import gi
gi.require_version("Gtk", "3.0")
gi.require_version("Pango", "1.0")
gi.require_version("PangoCairo", "1.0")
from gi.repository import Gtk, Gdk, Pango, PangoCairo
import cairo
import math
from typing import List, Callable
from data import Todo
from theme import Theme, set_color, rounded_rect


class TodoItemWidget(Gtk.DrawingArea):
    def __init__(self, todo: Todo, on_toggle: Callable[[int], None]):
        super().__init__()
        self._todo = todo
        self._on_toggle = on_toggle
        self.set_size_request(-1, Theme.ITEM_H)
        self.add_events(Gdk.EventMask.BUTTON_PRESS_MASK)
        self.connect("draw", self._on_draw)
        self.connect("button-press-event", self._on_click)

    def _on_draw(self, _widget, cr):
        w = self.get_allocated_width()
        h = self.get_allocated_height()

        # Background
        set_color(cr, Theme.SURFACE_C)
        rounded_rect(cr, 0, 0, w, h, 4)
        cr.fill()

        # Checkbox
        cx = Theme.CB_PAD_L + Theme.CB_SIZE / 2.0
        cy = h / 2.0
        r = Theme.CB_SIZE / 2.0

        if self._todo.is_completed:
            set_color(cr, Theme.CB_BDR_C)
            cr.set_line_width(2.0)
            cr.arc(cx, cy, r - 1, 0, 2 * math.pi)
            cr.stroke()
            set_color(cr, Theme.ACCENT_C)
            cr.set_line_width(1.5)
            cr.set_line_cap(cairo.LINE_CAP_ROUND)
            cr.set_line_join(cairo.LINE_JOIN_ROUND)
            cr.new_path()
            cr.move_to(cx - 4, cy)
            cr.line_to(cx - 1, cy + 3)
            cr.line_to(cx + 4, cy - 3)
            cr.stroke()
        else:
            set_color(cr, Theme.CB_BDR_C)
            cr.set_line_width(2)
            cr.arc(cx, cy, r - 1, 0, 2 * math.pi)
            cr.stroke()

        # Text
        tx = Theme.CB_PAD_L + Theme.CB_SIZE + Theme.CB_MR
        layout = PangoCairo.create_layout(cr)
        layout.set_text(self._todo.task, -1)
        desc = Pango.FontDescription.from_string("Sans 10")
        layout.set_font_description(desc)

        if self._todo.is_completed:
            attrs = Pango.AttrList()
            strike = Pango.attr_strikethrough_new(True)
            attrs.insert(strike)
            layout.set_attributes(attrs)

        color = Theme.MUTED_C if self._todo.is_completed else Theme.TEXT_C
        set_color(cr, color)
        _ink, logical = layout.get_pixel_extents()
        ty = (h - logical.height) / 2.0
        cr.move_to(tx, ty)
        PangoCairo.show_layout(cr, layout)

    def _on_click(self, _widget, event):
        cx = Theme.CB_PAD_L
        cy = (Theme.ITEM_H - Theme.CB_SIZE) / 2.0
        if cx <= event.x <= cx + Theme.CB_SIZE and cy <= event.y <= cy + Theme.CB_SIZE:
            self._on_toggle(self._todo.id)


class TodoList(Gtk.ScrolledWindow):
    def __init__(self, on_toggle: Callable[[int], None]):
        super().__init__()
        self._on_toggle = on_toggle
        self.set_policy(Gtk.PolicyType.NEVER, Gtk.PolicyType.AUTOMATIC)
        self.set_vexpand(True)

        self._vbox = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=Theme.ITEM_MB)
        self._vbox.set_valign(Gtk.Align.START)
        self.add(self._vbox)

    def refresh(self, todos: List[Todo]):
        for child in self._vbox.get_children():
            self._vbox.remove(child)
        for todo in todos:
            item = TodoItemWidget(todo, self._on_toggle)
            self._vbox.pack_start(item, False, False, 0)
        self._vbox.show_all()