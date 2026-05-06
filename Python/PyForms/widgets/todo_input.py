from PyQt5.QtWidgets import QLineEdit
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QPainter, QColor, QPen
from typing import Callable
from theme import Theme


class TodoInput(QLineEdit):
    def __init__(self, on_submit: Callable[[str], None], parent=None):
        super().__init__(parent)
        self._on_submit = on_submit
        self.setPlaceholderText("Add Task")
        self.setFixedHeight(Theme.ITEM_H)
        self.setStyleSheet(
            f"QLineEdit {{ background-color: {Theme.INPUT}; color: {Theme.WHITE};"
            f"  border: none; border-radius: 4px; font-size: 14px;"
            f"  padding: 4px 16px; }}"
            f"QLineEdit::placeholder {{ color: {Theme.MUTED}; }}"
        )
        self.returnPressed.connect(self._handle_submit)

    def _handle_submit(self):
        text = self.text().strip()
        if text:
            self._on_submit(text)
            self.clear()

    def paintEvent(self, event):
        super().paintEvent(event)
        if self.hasFocus():
            p = QPainter(self)
            p.setRenderHint(QPainter.Antialiasing)
            p.setBrush(Qt.NoBrush)
            p.setPen(QPen(QColor(Theme.ACCENT), 1))
            p.drawRoundedRect(0, 0, self.width() - 1, self.height() - 1, 4, 4)
            p.end()