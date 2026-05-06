#pragma once
#include <gtkmm.h>
#include <string>

class TodoInput : public Gtk::Overlay {
public:
    sigc::signal<void, std::string> signal_submitted;

    TodoInput();

private:
    Gtk::DrawingArea bg_;
    Gtk::Entry       entry_;

    bool on_draw_bg(const Cairo::RefPtr<Cairo::Context>& cr);
    void on_enter();
};