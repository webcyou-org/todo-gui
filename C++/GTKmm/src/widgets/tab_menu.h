#pragma once
#include <gtkmm.h>
#include <vector>
#include "../data.h"

class TabMenu : public Gtk::Box {
public:
    sigc::signal<void, TabFilter> signal_changed;

    TabMenu();
    void set_active(TabFilter f);

private:
    std::vector<Gtk::Button*> btns_;

    void on_click(TabFilter f);
};