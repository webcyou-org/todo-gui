from PyQt5.QtWidgets import QWidget, QVBoxLayout, QScrollArea
from PyQt5.QtCore import Qt, QPointF, QRectF
from PyQt5.QtGui import QPainter, QColor, QPen, QFont, QFontMetrics
from typing import List, Callable
from data import Todo
from theme import Theme


class TodoItemWidget(QWidget):
    def __init__(self, todo: Todo, on_toggle: Callable[[int], None], parent=None):
        super().__init__(parent)
        self._todo = todo
        self._on_toggle = on_toggle
        self.setFixedHeight(Theme.ITEM_H)
        self.setAttribute(Qt.WA_StyledBackground, False)
        self.setCursor(Qt.ArrowCursor)

    def paintEvent(self, event):
        p = QPainter(self)
        p.setRenderHint(QPainter.Antialiasing)
        w, h = self.width(), self.height()

        # Background
        p.setBrush(QColor(Theme.SURFACE))
        p.setPen(Qt.NoPen)
        p.drawRoundedRect(QRectF(0, 0, w, h), 4, 4)

        # Checkbox
        cx = Theme.CB_PAD_L
        cy = (h - Theme.CB_SIZE) // 2
        cs = Theme.CB_SIZE

        if self._todo.is_completed:
            p.setBrush(QColor(Theme.ACCENT))
            p.setPen(Qt.NoPen)
            p.drawEllipse(cx, cy, cs, cs)
            p.setPen(QPen(QColor(Theme.WHITE), 1.5, Qt.SolidLine,
                          Qt.RoundCap, Qt.RoundJoin))
            p.setBrush(Qt.NoBrush)
            ccx = cx + cs / 2.0
            ccy = cy + cs / 2.0
            p.drawPolyline(
                QPointF(ccx - 4, ccy),
                QPointF(ccx - 1, ccy + 3),
                QPointF(ccx + 4, ccy - 3),
            )
        else:
            p.setBrush(Qt.NoBrush)
            p.setPen(QPen(QColor(Theme.CB_BDR), 2))
            p.drawEllipse(cx + 1, cy + 1, cs - 2, cs - 2)

        # Text
        tx = Theme.CB_PAD_L + Theme.CB_SIZE + Theme.CB_MR
        font = QFont("Sans", 10)
        font.setStrikeOut(self._todo.is_completed)
        p.setFont(font)
        p.setPen(QColor(Theme.MUTED if self._todo.is_completed else Theme.TEXT))
        fm = QFontMetrics(font)
        ty = (h - fm.height()) // 2
        p.drawText(tx, ty, w - tx - 10, fm.height(),
                   Qt.AlignLeft | Qt.AlignVCenter, self._todo.task)
        p.end()

    def mousePressEvent(self, event):
        x, y = event.x(), event.y()
        cx = Theme.CB_PAD_L
        cy = (Theme.ITEM_H - Theme.CB_SIZE) // 2
        if cx <= x <= cx + Theme.CB_SIZE and cy <= y <= cy + Theme.CB_SIZE:
            self._on_toggle(self._todo.id)


class TodoList(QScrollArea):
    def __init__(self, on_toggle: Callable[[int], None], parent=None):
        super().__init__(parent)
        self._on_toggle = on_toggle
        self.setWidgetResizable(True)
        self.setHorizontalScrollBarPolicy(Qt.ScrollBarAlwaysOff)
        self.setStyleSheet(
            f"QScrollArea {{ background-color: {Theme.BG}; border: none; }}"
            f"QWidget#list_container {{ background-color: {Theme.BG}; }}"
        )

        self._container = QWidget()
        self._container.setObjectName("list_container")
        self._vbox = QVBoxLayout(self._container)
        self._vbox.setContentsMargins(0, 0, 0, 0)
        self._vbox.setSpacing(Theme.ITEM_MB)
        self._vbox.addStretch()
        self.setWidget(self._container)

    def refresh(self, todos: List[Todo]):
        while self._vbox.count() > 1:
            item = self._vbox.takeAt(0)
            if item.widget():
                item.widget().deleteLater()

        for todo in todos:
            widget = TodoItemWidget(todo, self._on_toggle)
            self._vbox.insertWidget(self._vbox.count() - 1, widget)