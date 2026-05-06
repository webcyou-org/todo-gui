"""Todo input widget."""
import remi.gui as gui
from theme import Theme


def build_todo_input(on_submit):
    """Return (container_widget, input_widget)."""
    inp = gui.TextInput()
    inp.attributes['placeholder'] = 'Add Task'
    inp.style.update({
        'background-color': Theme.INPUT,
        'color': Theme.WHITE,
        'height': Theme.ITEM_H,
        'border-radius': '4px',
        'border': '1px solid transparent',
        'padding': '4px 16px',
        'font-size': '14px',
        'width': '100%',
        'outline': 'none',
        'box-sizing': 'border-box',
        'margin-bottom': '14px',
    })

    def on_key_up(widget, value, keycode):
        if keycode == '13':
            task = value.strip()
            if task:
                on_submit(task)
                widget.set_value('')

    inp.onkeyup.do(on_key_up)
    return inp