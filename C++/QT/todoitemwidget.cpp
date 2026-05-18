#include "todoitemwidget.h"
#include "theme.h"
#include <QPainter>
#include <QMouseEvent>

TodoItemWidget::TodoItemWidget(const Todo &todo, QWidget *parent)
    : QWidget(parent), m_todo(todo) {
    setFixedHeight(Theme::ITEM_H);
    setCursor(Qt::PointingHandCursor);
}

void TodoItemWidget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // Background
    p.setPen(Qt::NoPen);
    p.setBrush(Theme::SURFACE);
    p.drawRoundedRect(rect(), 4, 4);

    // Checkbox
    int cbX = Theme::CB_PAD_L;
    int cbY = (height() - Theme::CB_SIZE) / 2;
    m_cbRect = QRect(cbX, cbY, Theme::CB_SIZE, Theme::CB_SIZE);

    if (m_todo.isCompleted) {
        p.setBrush(Qt::NoBrush);
        p.setPen(QPen(Theme::CB_BORDER, 1));
        p.drawEllipse(m_cbRect);

        // Checkmark in accent color
        p.setPen(QPen(Theme::ACCENT, 1.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        int cx = cbX + Theme::CB_SIZE / 2;
        int cy = cbY + Theme::CB_SIZE / 2;
        QPolygonF mark;
        mark << QPointF(cx - 4, cy)
             << QPointF(cx - 1, cy + 3)
             << QPointF(cx + 4, cy - 3);
        p.drawPolyline(mark);
    } else {
        p.setBrush(Qt::NoBrush);
        p.setPen(QPen(Theme::CB_BORDER, 1));
        p.drawEllipse(m_cbRect);
    }

    // Task text
    QFont font = p.font();
    font.setPixelSize(14);
    font.setStrikeOut(m_todo.isCompleted);
    p.setFont(font);
    p.setPen(m_todo.isCompleted ? Theme::MUTED : Theme::TEXT);

    int textX = Theme::LABEL_X;
    QRect textRect(textX, 0, width() - textX - Theme::CONTENT_H, height());
    p.drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, m_todo.task);
}

void TodoItemWidget::mousePressEvent(QMouseEvent *event) {
    if (m_cbRect.contains(event->pos())) {
        emit toggleRequested(m_todo.id);
    }
}