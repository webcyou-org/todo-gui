#pragma once
#include <QObject>
#include <QVector>
#include "data.h"

class TodoModel : public QObject {
    Q_OBJECT
public:
    explicit TodoModel(QObject *parent = nullptr);

    void addTodo(const QString &task);
    void toggleCompleted(int id);
    QVector<Todo> filteredTodos(TabFilter filter) const;

private:
    QVector<Todo> m_todos;
    int           m_nextId = 1;

    void addSample(const QString &task, bool completed = false);
};

class MenuModel : public QObject {
    Q_OBJECT
public:
    explicit MenuModel(QObject *parent = nullptr);

    TabFilter activeTab() const      { return m_activeTab; }
    void      setActiveTab(TabFilter tab) { m_activeTab = tab; }

private:
    TabFilter m_activeTab = TabFilter::All;
};