#include "data.h"

TodoModel::TodoModel() {
    Todo t1; t1.id = next_id++; t1.task = "Task 1"; t1.is_completed = false;
    Todo t2; t2.id = next_id++; t2.task = "Task 2"; t2.is_completed = true;
    Todo t3; t3.id = next_id++; t3.task = "Task 3"; t3.is_completed = false;
    Todo t4; t4.id = next_id++; t4.task = "Task 4"; t4.is_completed = false;
    todos.Add(t1);
    todos.Add(t2);
    todos.Add(t3);
    todos.Add(t4);
}

void TodoModel::addTodo(const String& task) {
    if(task.IsEmpty()) return;
    Todo t;
    t.id           = next_id++;
    t.task         = task;
    t.is_completed = false;
    todos.Add(t);
}

Todo* TodoModel::findById(int id) {
    for(auto& t : todos)
        if(t.id == id) return &t;
    return nullptr;
}

void TodoModel::changeCompleted(int id) {
    if(Todo* t = findById(id))
        t->is_completed = !t->is_completed;
}

Vector<Todo> TodoModel::getFilteredTodos(TabFilter filter) const {
    Vector<Todo> result;
    for(const auto& t : todos) {
        bool include =
            (filter == TabFilter::All) ||
            (filter == TabFilter::Active    && !t.is_completed) ||
            (filter == TabFilter::Completed &&  t.is_completed);
        if(include)
            result.Add(t);
    }
    return result;
}

void TodoModel::removeData(int id) {
    for(int i = 0; i < todos.GetCount(); i++) {
        if(todos[i].id == id) {
            todos.Remove(i);
            return;
        }
    }
}