from PyQt6.QtWidgets import QLineEdit
from PyQt6.QtGui import QPalette
import theme


class TodoInput(QLineEdit):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setFixedHeight(theme.INPUT_H)
        self.setPlaceholderText("Add Task")
        self.setStyleSheet(f"""
            QLineEdit {{
                background: {theme.C_INPUT.name()};
                color: {theme.C_WHITE.name()};
                border: 1px solid transparent;
                border-radius: 4px;
                padding: 4px 16px;
            }}
            QLineEdit:focus {{
                border: 1px solid {theme.C_ACCENT.name()};
            }}
        """)
        pal = self.palette()
        pal.setColor(QPalette.ColorRole.PlaceholderText, theme.C_MUTED)
        self.setPalette(pal)