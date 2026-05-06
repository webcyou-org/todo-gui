#include "tab_menu.h"
#include "../theme.h"

TabMenu::TabMenu() : Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 0) {
    set_size_request(-1, 28);
    const struct { TabFilter f; const char* label; } tabs[] = {
        { TabFilter::All,       "All"       },
        { TabFilter::Active,    "Active"    },
        { TabFilter::Completed, "Completed" },
    };
    for (auto& t : tabs) {
        auto* btn = Gtk::make_managed<Gtk::Button>(t.label);
        btn->get_style_context()->add_class("tab-btn");
        btn->set_relief(Gtk::RELIEF_NONE);
        btn->set_focus_on_click(false);
        TabFilter f = t.f;
        btn->signal_clicked().connect([this, f](){ on_click(f); });
        btns_.push_back(btn);
        pack_start(*btn, false, false, 0);
    }
    set_active(TabFilter::All);
}

void TabMenu::set_active(TabFilter f) {
    for (int i = 0; i < 3; ++i) {
        auto ctx = btns_[i]->get_style_context();
        if (static_cast<int>(f) == i) ctx->add_class("tab-btn-active");
        else                           ctx->remove_class("tab-btn-active");
    }
}

void TabMenu::on_click(TabFilter f) {
    set_active(f);
    signal_changed.emit(f);
}