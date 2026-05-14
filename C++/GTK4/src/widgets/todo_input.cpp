#include "todo_input.h"
#include "../app.h"

static void draw_input_bg(GtkDrawingArea*, cairo_t* cr,
                           int width, int height, gpointer user_data) {
    auto* entry = static_cast<GtkWidget*>(user_data);
    cr_color(cr, Theme::INPUT);
    cr_rounded_rect(cr, 0, 0, width, height, 4.0);
    cairo_fill(cr);
    if (gtk_widget_has_focus(entry)) {
        cr_color(cr, Theme::ACCENT);
        cairo_set_line_width(cr, 1.0);
        cr_rounded_rect(cr, 0.5, 0.5, width - 1, height - 1, 4.0);
        cairo_stroke(cr);
    }
}

GtkWidget* build_input(App* app) {
    GtkWidget* overlay = gtk_overlay_new();
    gtk_widget_set_size_request(overlay, -1, 35);

    GtkWidget* bg = gtk_drawing_area_new();
    gtk_widget_set_size_request(bg, -1, 35);
    gtk_overlay_set_child(GTK_OVERLAY(overlay), bg);

    GtkWidget* entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Add Task");
    gtk_widget_add_css_class(entry, "todo-entry");
    gtk_entry_set_has_frame(GTK_ENTRY(entry), FALSE);
    gtk_widget_set_margin_start(entry, 1);
    gtk_widget_set_margin_end(entry, 1);
    gtk_widget_set_margin_top(entry, 1);
    gtk_widget_set_margin_bottom(entry, 1);
    gtk_widget_set_valign(entry, GTK_ALIGN_FILL);
    gtk_widget_set_halign(entry, GTK_ALIGN_FILL);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), entry);

    app->entry = entry;
    app->entry_bg = bg;
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(bg), draw_input_bg, entry, nullptr);

    GtkEventController* focus = gtk_event_controller_focus_new();
    gtk_widget_add_controller(entry, focus);
    g_signal_connect(focus, "enter", G_CALLBACK(
        +[](GtkEventControllerFocus*, gpointer ud) {
            gtk_widget_queue_draw(GTK_WIDGET(ud)); }), bg);
    g_signal_connect(focus, "leave", G_CALLBACK(
        +[](GtkEventControllerFocus*, gpointer ud) {
            gtk_widget_queue_draw(GTK_WIDGET(ud)); }), bg);

    g_signal_connect(entry, "activate", G_CALLBACK(
        +[](GtkEntry* e, gpointer ud) {
            auto* a = static_cast<App*>(ud);
            std::string text = gtk_editable_get_text(GTK_EDITABLE(e));
            auto s = text.find_first_not_of(" \t");
            if (s == std::string::npos) { gtk_editable_set_text(GTK_EDITABLE(e), ""); return; }
            text = text.substr(s, text.find_last_not_of(" \t") - s + 1);
            gtk_editable_set_text(GTK_EDITABLE(e), "");
            a->model.add_todo(text);
            a->refresh_list();
        }), app);

    return overlay;
}