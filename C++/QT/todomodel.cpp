#include "todomodel.h"

MenuModel::MenuModel(QObject *parent) : QObject(parent) {}

TodoModel::TodoModel(QObject *parent) : QObject(parent) {
    addSample("Buy groceries");
    addSample("Walk the dog", true);
    addSample("Read a book");
}

void TodoModel::addTodo(const QString &task) {
    m_todos.append({m_nextId++, task, false});
}

void TodoModel::toggleCompleted(int id) {
    for (auto &todo : m_todos) {
        if (todo.id == id) {
            todo.isCompleted = !todo.isCompleted;
            return;
        }
    }
}

QVector<Todo> TodoModel::filteredTodos(TabFilter filter) const {
    if (filter == TabFilter::All) return m_todos;
    QVector<Todo> result;
    for (const auto &todo : m_todos) {
        bool keep = (filter == TabFilter::Completed) ? todo.isCompleted : !todo.isCompleted;
        if (keep) result.append(todo);
    }
    return result;
}

void TodoModel::addSample(const QString &task, bool completed) {
    m_todos.append({m_nextId++, task, completed});
}