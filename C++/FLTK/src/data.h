#pragma once
#include <string>
#include <vector>

enum class TabFilter { All, Active, Completed };

struct Todo {
    int         id;
    std::string task;
    bool        isCompleted;
};

class TodoModel {
public:
    TodoModel() {
        sample("Task1", false);
        sample("Task2", true);
        sample("Task3", false);
        sample("Task4", false);
    }

    void addTodo(const std::string& task) {
        m_todos.push_back({ m_nextId++, task, false });
    }

    void toggleCompleted(int id) {
        for (auto& t : m_todos)
            if (t.id == id) { t.isCompleted = !t.isCompleted; return; }
    }

    std::vector<Todo> filteredTodos(TabFilter filter) const {
        if (filter == TabFilter::All) return m_todos;
        std::vector<Todo> out;
        for (const auto& t : m_todos)
            if ((filter == TabFilter::Completed) == t.isCompleted)
                out.push_back(t);
        return out;
    }

private:
    std::vector<Todo> m_todos;
    int               m_nextId = 1;

    void sample(const std::string& task, bool completed) {
        m_todos.push_back({ m_nextId++, task, completed });
    }
};

class MenuModel {
public:
    TabFilter activeTab = TabFilter::All;
};