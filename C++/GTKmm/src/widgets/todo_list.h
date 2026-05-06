#pragma once
#include <gtkmm.h>
#include <vector>
#include "../data.h"

class TodoItemWidget : public Gtk::DrawingArea {
public:
    sigc::signal<void, int> signal_toggle;

    explicit TodoItemWidget(const Todo& todo);

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    bool on_button_press_event(GdkEventButton* ev) override;

private:
    Todo todo_;
};

class TodoList : public Gtk::ScrolledWindow {
public:
    sigc::signal<void, int> signal_toggle;

    TodoList();
    void refresh(const std::vector<Todo>& todos);

private:
    Gtk::Box                     vbox_{Gtk::ORIENTATION_VERTICAL};
    std::vector<TodoItemWidget*> items_;
};