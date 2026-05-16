#pragma once
#include <string>
#include <vector>
#include <algorithm>

// ── Entities ─────────────────────────────────────────────────────────────────

struct Todo {
    int         id;
    std::string task;
    bool        is_completed;
};

enum class TabFilter { All, Active, Completed };

// ── TodoModel ─────────────────────────────────────────────────────────────────

class TodoModel {
    std::vector<Todo> list_;
    int               next_id_ = 1;
public:
    TodoModel() {
        list_ = {
            {next_id_++, "Task 1", false},
            {next_id_++, "Task 2", true },
            {next_id_++, "Task 3", false},
            {next_id_++, "Task 4", false},
        };
    }

    const std::vector<Todo>& getData() const { return list_; }

    void addTodo(const std::string& task) {
        if (task.empty()) return;
        list_.push_back({next_id_++, task, false});
    }

    void toggleCompleted(int id) {
        for (auto& t : list_)
            if (t.id == id) { t.is_completed = !t.is_completed; return; }
    }

    void removeData(int id) {
        list_.erase(std::remove_if(list_.begin(), list_.end(),
            [id](const Todo& t) { return t.id == id; }), list_.end());
    }

    std::vector<Todo> filteredTodos(TabFilter tab) const {
        std::vector<Todo> out;
        for (const auto& t : list_) {
            if (tab == TabFilter::All ||
                (tab == TabFilter::Active    && !t.is_completed) ||
                (tab == TabFilter::Completed &&  t.is_completed))
                out.push_back(t);
        }
        return out;
    }
};

// ── MenuModel ─────────────────────────────────────────────────────────────────

class MenuModel {
    TabFilter active_ = TabFilter::All;
public:
    TabFilter activeTab() const { return active_; }
    void setActiveTab(TabFilter t) { active_ = t; }

    static const char* label(TabFilter t) {
        switch (t) {
            case TabFilter::All:       return "All";
            case TabFilter::Active:    return "Active";
            case TabFilter::Completed: return "Completed";
        }
        return "";
    }
};