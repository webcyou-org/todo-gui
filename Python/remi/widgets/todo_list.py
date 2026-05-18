"""Todo list widgets."""
import remi.gui as gui
from typing import List, Callable
from data import Todo
from theme import Theme


def _make_toggle_cb(todo_id: int, on_toggle: Callable):
    def cb(widget):
        on_toggle(todo_id)
    return cb


def build_todo_item(todo: Todo, on_toggle: Callable) -> gui.HBox:
    item = gui.HBox()
    item.style.update({
        'background-color': Theme.SURFACE,
        'height': Theme.ITEM_H,
        'min-height': Theme.ITEM_H,
        'border-radius': '4px',
        'padding': '0 10px',
        'align-items': 'center',
        'width': '100%',
        'box-sizing': 'border-box',
        'margin-bottom': Theme.ITEM_MB,
        'flex-shrink': '0',
        'gap': Theme.CB_MR,
    })

    # Circular checkbox
    cb = gui.VBox()
    cb.style.update({
        'width': '16px',
        'height': '16px',
        'min-width': '16px',
        'border-radius': '8px',
        'flex-shrink': '0',
        'cursor': 'pointer',
        'display': 'flex',
        'align-items': 'center',
        'justify-content': 'center',
        'box-sizing': 'border-box',
    })
    if todo.is_completed:
        cb.style['border'] = f'2px solid {Theme.CB_BDR}'
        check = gui.Label("✓")
        check.style.update({
            'color': Theme.ACCENT,
            'font-size': '10px',
            'line-height': '1',
            'pointer-events': 'none',
        })
        cb.append(check)
    else:
        cb.style['border'] = f'2px solid {Theme.CB_BDR}'
    cb.onclick.do(_make_toggle_cb(todo.id, on_toggle))
    item.append(cb)

    # Task text
    text = gui.Label(todo.task)
    text.style.update({
        'font-size': '14px',
        'color': Theme.MUTED if todo.is_completed else Theme.TEXT,
    })
    if todo.is_completed:
        text.style['text-decoration'] = 'line-through'
    item.append(text)

    return item


class TodoList(gui.VBox):
    def __init__(self, on_toggle: Callable):
        super().__init__()
        self._on_toggle = on_toggle
        self.style.update({
            'flex': '1',
            'overflow-y': 'auto',
            'width': '100%',
        })

    def refresh(self, todos: List[Todo]):
        self.empty()
        for todo in todos:
            self.append(build_todo_item(todo, self._on_toggle))