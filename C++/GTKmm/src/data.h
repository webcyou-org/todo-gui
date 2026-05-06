#pragma once
#include <vector>
#include <string>

enum class TabFilter { All, Active, Completed };

struct Todo {
    int         id;
    std::string task;
    bool        is_completed;
};

class TodoModel {
public:
    TodoModel() {
        sample("Task1", false);
        sample("Task2", true);
        sample("Task3", false);
        sample("Task4", false);
    }

    void add_todo(const std::string& task) {
        todos_.push_back({next_id_++, task, false});
    }

    void toggle(int id) {
        for (auto& t : todos_)
            if (t.id == id) { t.is_completed = !t.is_completed; return; }
    }

    std::vector<Todo> filtered(TabFilter f) const {
        if (f == TabFilter::All) return todos_;
        std::vector<Todo> out;
        for (const auto& t : todos_)
            if (t.is_completed == (f == TabFilter::Completed))
                out.push_back(t);
        return out;
    }

private:
    std::vector<Todo> todos_;
    int               next_id_ = 1;

    void sample(const std::string& task, bool completed) {
        todos_.push_back({next_id_++, task, completed});
    }
};

class MenuModel {
public:
    TabFilter active_tab = TabFilter::All;
};