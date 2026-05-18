from PySide6.QtWidgets import QWidget, QVBoxLayout, QScrollArea, QFrame
from PySide6.QtCore import Signal, Qt, QRect, QPointF
from PySide6.QtGui import QPainter, QPen, QPolygonF, QFont
import theme
from data import Todo


class TodoItemWidget(QWidget):
    toggle_requested = Signal(int)

    def __init__(self, todo: Todo, parent=None):
        super().__init__(parent)
        self._todo = todo
        self._cb_rect = QRect(0, 0, 0, 0)
        self.setFixedHeight(theme.ITEM_H)
        self.setCursor(Qt.CursorShape.PointingHandCursor)

    def paintEvent(self, event):
        p = QPainter(self)
        p.setRenderHint(QPainter.RenderHint.Antialiasing)

        # Background
        p.setPen(Qt.PenStyle.NoPen)
        p.setBrush(theme.C_SURFACE)
        p.drawRoundedRect(self.rect(), 4, 4)

        # Checkbox
        cb_x = theme.CB_PAD_L
        cb_y = (self.height() - theme.CB_SIZE) // 2
        self._cb_rect = QRect(cb_x, cb_y, theme.CB_SIZE, theme.CB_SIZE)

        if self._todo.is_completed:
            p.setBrush(Qt.BrushStyle.NoBrush)
            p.setPen(QPen(theme.C_CB_BORDER, 1))
            p.drawEllipse(self._cb_rect)

            pen = QPen(theme.C_ACCENT, 1.5)
            pen.setCapStyle(Qt.PenCapStyle.RoundCap)
            pen.setJoinStyle(Qt.PenJoinStyle.RoundJoin)
            p.setPen(pen)
            cx = cb_x + theme.CB_SIZE / 2
            cy = cb_y + theme.CB_SIZE / 2
            mark = QPolygonF([
                QPointF(cx - 4, cy),
                QPointF(cx - 1, cy + 3),
                QPointF(cx + 4, cy - 3),
            ])
            p.drawPolyline(mark)
        else:
            p.setBrush(Qt.BrushStyle.NoBrush)
            p.setPen(QPen(theme.C_CB_BORDER, 1))
            p.drawEllipse(self._cb_rect)

        # Task text
        font = QFont()
        font.setPixelSize(14)
        font.setStrikeOut(self._todo.is_completed)
        p.setFont(font)
        p.setPen(theme.C_MUTED if self._todo.is_completed else theme.C_TEXT)

        text_rect = QRect(
            theme.LABEL_X, 0,
            self.width() - theme.LABEL_X - theme.CONTENT_H,
            self.height(),
        )
        p.drawText(text_rect, Qt.AlignmentFlag.AlignVCenter | Qt.AlignmentFlag.AlignLeft,
                   self._todo.task)

    def mousePressEvent(self, event):
        if self._cb_rect.contains(event.pos()):
            self.toggle_requested.emit(self._todo.id)


class TodoList(QWidget):
    toggle_requested = Signal(int)

    def __init__(self, parent=None):
        super().__init__(parent)
        outer = QVBoxLayout(self)
        outer.setContentsMargins(0, 0, 0, 0)
        outer.setSpacing(0)

        self._scroll = QScrollArea()
        self._scroll.setWidgetResizable(True)
        self._scroll.setFrameShape(QFrame.Shape.NoFrame)
        self._scroll.setHorizontalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAlwaysOff)
        self._scroll.setStyleSheet("QScrollArea { background: transparent; border: none; }")
        self._scroll.viewport().setStyleSheet("background: transparent;")

        self._container = QWidget()
        self._container.setAutoFillBackground(False)
        self._container.setStyleSheet("background: transparent;")

        self._list_layout = QVBoxLayout(self._container)
        self._list_layout.setContentsMargins(0, 0, 0, 0)
        self._list_layout.setSpacing(theme.ITEM_MB)
        self._list_layout.addStretch()

        self._scroll.setWidget(self._container)
        outer.addWidget(self._scroll)

    def refresh(self, todos: list[Todo]):
        while self._list_layout.count() > 1:
            item = self._list_layout.takeAt(0)
            if item.widget():
                item.widget().deleteLater()

        for todo in todos:
            row = TodoItemWidget(todo, self._container)
            row.toggle_requested.connect(self.toggle_requested)
            self._list_layout.insertWidget(self._list_layout.count() - 1, row)