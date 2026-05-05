#pragma once
#include <wx/string.h>
#include <vector>

enum class TabFilter { All, Active, Completed };

struct Todo {
    int      id;
    wxString task;
    bool     isCompleted;
};

class TodoModel {
public:
    TodoModel() {
        addSample("Task1");
        addSample("Task2", true);
        addSample("Task3");
        addSample("Task4");
    }

    void addTodo(const wxString& task) {
        m_todos.push_back({ m_nextId++, task, false });
    }

    void toggleCompleted(int id) {
        for (auto& t : m_todos)
            if (t.id == id) { t.isCompleted = !t.isCompleted; return; }
    }

    std::vector<Todo> filteredTodos(TabFilter filter) const {
        if (filter == TabFilter::All) return m_todos;
        std::vector<Todo> result;
        for (const auto& t : m_todos)
            if ((filter == TabFilter::Completed) == t.isCompleted)
                result.push_back(t);
        return result;
    }

private:
    std::vector<Todo> m_todos;
    int               m_nextId = 1;

    void addSample(const wxString& task, bool completed = false) {
        m_todos.push_back({ m_nextId++, task, completed });
    }
};

class MenuModel {
public:
    TabFilter activeTab = TabFilter::All;
};