#pragma once
#include <QWidget>
#include "data.h"

class TodoItemWidget : public QWidget {
    Q_OBJECT
public:
    explicit TodoItemWidget(const Todo &todo, QWidget *parent = nullptr);

signals:
    void toggleRequested(int id);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Todo  m_todo;
    QRect m_cbRect;
};