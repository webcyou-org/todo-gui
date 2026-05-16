#pragma once
#include <string>
#include <vector>

enum class TabFilter { All, Active, Completed };

struct Todo {
    int         id;
    std::string task;
    bool        is_completed;
};

class TodoModel {
public:
    TodoModel() {
        add_sample("Task 1", false);
        add_sample("Task 2", true);
        add_sample("Task 3", false);
        add_sample("Task 4", false);
    }

    void add_todo(const std::string& task) {
        if (!task.empty())
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

    void add_sample(const std::string& task, bool done) {
        todos_.push_back({next_id_++, task, done});
    }
};