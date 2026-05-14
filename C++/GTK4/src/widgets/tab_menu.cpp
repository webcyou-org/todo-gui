#include "tab_menu.h"
#include "../app.h"

struct TabClickData { App* app; TabFilter filter; };

GtkWidget* build_tabs(App* app) {
    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(box, -1, 28);

    const struct { TabFilter f; const char* label; } tabs[] = {
        { TabFilter::All,       "All"       },
        { TabFilter::Active,    "Active"    },
        { TabFilter::Completed, "Completed" },
    };

    for (int i = 0; i < 3; ++i) {
        GtkWidget* btn = gtk_button_new_with_label(tabs[i].label);
        gtk_widget_add_css_class(btn, "tab-btn");
        gtk_button_set_has_frame(GTK_BUTTON(btn), FALSE);
        gtk_widget_set_focus_on_click(btn, FALSE);

        auto* data = new TabClickData{app, tabs[i].f};
        g_object_set_data_full(G_OBJECT(btn), "tab-data", data,
            [](gpointer p) { delete static_cast<TabClickData*>(p); });

        g_signal_connect(btn, "clicked", G_CALLBACK(
            +[](GtkButton* b, gpointer) {
                auto* d = static_cast<TabClickData*>(
                    g_object_get_data(G_OBJECT(b), "tab-data"));
                d->app->active_tab = d->filter;
                d->app->update_tab_styles();
                d->app->refresh_list();
            }), nullptr);

        app->tab_btns[i] = btn;
        gtk_box_append(GTK_BOX(box), btn);
    }
    app->update_tab_styles();
    return box;
}