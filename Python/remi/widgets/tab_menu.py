"""Tab menu widget."""
import remi.gui as gui
from data import TabFilter
from theme import Theme

TAB_LABELS = [
    (TabFilter.ALL,       "All"),
    (TabFilter.ACTIVE,    "Active"),
    (TabFilter.COMPLETED, "Completed"),
]


class TabMenu(gui.HBox):
    def __init__(self, on_change):
        super().__init__()
        self._on_change = on_change
        self._buttons = {}
        self.style.update({
            'margin-bottom': '3px',
            'align-items': 'center',
        })

        for f, label in TAB_LABELS:
            btn = gui.Label(label)
            btn.style.update({
                'color': Theme.TEXT,
                'font-size': '14px',
                'line-height': '28px',
                'padding': '0 8px',
                'cursor': 'pointer',
            })
            btn.onclick.do(self._make_cb(f))
            self._buttons[f] = btn
            self.append(btn)

    def _make_cb(self, f: TabFilter):
        def cb(widget):
            self._on_change(f)
        return cb

    def set_active(self, active: TabFilter):
        for f, btn in self._buttons.items():
            btn.style['font-weight'] = 'bold' if f == active else 'normal'