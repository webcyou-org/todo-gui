from PyQt5.QtWidgets import QWidget, QHBoxLayout, QPushButton
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QFont
from typing import Callable, List
from data import TabFilter
from theme import Theme

TAB_LABELS = [
    (TabFilter.ALL,       "All"),
    (TabFilter.ACTIVE,    "Active"),
    (TabFilter.COMPLETED, "Completed"),
]


class TabMenu(QWidget):
    def __init__(self, on_change: Callable[[TabFilter], None], parent=None):
        super().__init__(parent)
        self._on_change = on_change
        self._buttons: List[QPushButton] = []
        self.setFixedHeight(28)
        self.setStyleSheet(f"background-color: {Theme.BG};")

        layout = QHBoxLayout(self)
        layout.setContentsMargins(0, 0, 0, 0)
        layout.setSpacing(0)

        for f, label in TAB_LABELS:
            btn = QPushButton(label)
            btn.setCursor(Qt.PointingHandCursor)
            btn.setStyleSheet(
                f"QPushButton {{ background: transparent; border: none;"
                f" color: {Theme.TEXT}; font-size: 14px; padding: 0 8px;"
                f" min-height: 28px; }}"
                f"QPushButton:hover {{ background: transparent; }}"
            )
            btn.clicked.connect(lambda checked, fv=f: self._click(fv))
            self._buttons.append(btn)
            layout.addWidget(btn)

        layout.addStretch()
        self.set_active(TabFilter.ALL)

    def set_active(self, f: TabFilter):
        for i, (fv, _) in enumerate(TAB_LABELS):
            font = QFont()
            font.setPointSize(10)
            font.setBold(fv == f)
            self._buttons[i].setFont(font)

    def _click(self, f: TabFilter):
        self.set_active(f)
        self._on_change(f)