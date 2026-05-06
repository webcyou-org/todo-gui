#pragma once
#include <FL/Fl_Widget.H>
#include "../data.h"
#include <functional>
#include <vector>

class TodoList : public Fl_Widget {
    std::vector<Todo>        m_todos;
    std::function<void(int)> m_onToggle;
    int                      m_scrollY = 0;

    int totalH() const;
    int maxScroll() const;
    void drawItem(const Todo& todo, int iy);
    void draw() override;
    int  handle(int event) override;

public:
    TodoList(int x, int y, int w, int h, std::function<void(int)> cb);
    void refresh(const std::vector<Todo>& todos);
};