#pragma once
#include <gtk/gtk.h>
#include "data.h"
#include "theme.h"

struct App {
    TodoModel model;
    TabFilter active_tab = TabFilter::All;

    GtkWidget* entry    = nullptr;
    GtkWidget* entry_bg = nullptr;
    GtkWidget* list_box = nullptr;
    GtkWidget* tab_btns[3] = {};

    void update_tab_styles() {
        for (int i = 0; i < 3; ++i) {
            if (!tab_btns[i]) continue;
            if (static_cast<int>(active_tab) == i)
                gtk_widget_add_css_class(tab_btns[i], "active");
            else
                gtk_widget_remove_css_class(tab_btns[i], "active");
        }
    }

    void refresh_list();  // defined in main.cpp (needs widget includes)
};