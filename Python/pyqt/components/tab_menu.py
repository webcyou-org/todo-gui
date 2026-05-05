from PyQt6.QtWidgets import QWidget, QHBoxLayout, QLabel
from PyQt6.QtCore import pyqtSignal, Qt
from PyQt6.QtGui import QPalette, QFont
import theme
from data import TabFilter


class TabMenu(QWidget):
    tab_clicked = pyqtSignal(TabFilter)

    def __init__(self, parent=None):
        super().__init__(parent)
        layout = QHBoxLayout(self)
        layout.setContentsMargins(0, 0, 0, 0)
        layout.setSpacing(0)

        self._labels: dict[TabFilter, QLabel] = {}
        for tab, text in [
            (TabFilter.ALL, "All"),
            (TabFilter.ACTIVE, "Active"),
            (TabFilter.COMPLETED, "Completed"),
        ]:
            lbl = self._make_tab(text, tab)
            self._labels[tab] = lbl
            layout.addWidget(lbl)

        layout.addStretch()

    def _make_tab(self, text: str, tab: TabFilter) -> QLabel:
        lbl = QLabel(text)
        font = QFont()
        font.setPixelSize(14)
        lbl.setFont(font)
        pal = lbl.palette()
        pal.setColor(QPalette.ColorRole.WindowText, theme.C_TEXT)
        lbl.setPalette(pal)
        lbl.setContentsMargins(8, 0, 8, 0)
        lbl.setFixedHeight(28)
        lbl.setCursor(Qt.CursorShape.PointingHandCursor)
        lbl.mousePressEvent = lambda e, t=tab: self.tab_clicked.emit(t)
        return lbl

    def set_active(self, tab: TabFilter):
        for t, lbl in self._labels.items():
            font = lbl.font()
            font.setBold(t == tab)
            lbl.setFont(font)