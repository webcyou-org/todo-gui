#pragma once
#include <string>
#include <vector>

enum class TabFilter { All, Active, Completed };

struct Todo {
    int id;
    std::string task;
    bool is_completed;
};

struct AppState {
    std::vector<Todo> todos;
    TabFilter active_tab = TabFilter::All;
    std::string input_text;
    int next_id = 1;
    float scroll_offset = 0.0f;
    bool input_focused = false;

    AppState() {
        todos.push_back({next_id++, "Task 1", false});
        todos.push_back({next_id++, "Task 2", true});
        todos.push_back({next_id++, "Task 3", false});
        todos.push_back({next_id++, "Task 4", false});
    }

    void add_todo(const std::string& task) {
        if (!task.empty()) todos.push_back({next_id++, task, false});
    }

    void toggle_todo(int id) {
        for (auto& t : todos)
            if (t.id == id) { t.is_completed = !t.is_completed; return; }
    }

    std::vector<Todo> get_filtered() const {
        std::vector<Todo> out;
        for (const auto& t : todos) {
            if (active_tab == TabFilter::All ||
                (active_tab == TabFilter::Active    && !t.is_completed) ||
                (active_tab == TabFilter::Completed &&  t.is_completed))
                out.push_back(t);
        }
        return out;
    }
};