#include "app.h"
#include "widgets/todo_input.h"
#include "widgets/tab_menu.h"
#include "widgets/todo_list.h"

// ─── App::refresh_list ────────────────────────────────────────────────────────

void App::refresh_list() {
    if (!list_box) return;

    GtkWidget* child;
    while ((child = gtk_widget_get_first_child(list_box)) != nullptr)
        gtk_box_remove(GTK_BOX(list_box), child);

    for (const auto& todo : model.filtered(active_tab)) {
        GtkWidget* area = gtk_drawing_area_new();
        gtk_widget_set_size_request(area, -1, Theme::ITEM_H);
        gtk_widget_set_margin_bottom(area, Theme::ITEM_MB);

        auto* data = new TodoItemData{todo, this};
        g_object_set_data_full(G_OBJECT(area), "item-data", data,
            [](gpointer p) { delete static_cast<TodoItemData*>(p); });

        gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(area),
            draw_todo_item, data, nullptr);

        GtkGesture* click = gtk_gesture_click_new();
        gtk_widget_add_controller(area, GTK_EVENT_CONTROLLER(click));
        g_signal_connect(click, "pressed", G_CALLBACK(
            +[](GtkGestureClick* gesture, int, double x, double y, gpointer) {
                GtkWidget* w = gtk_event_controller_get_widget(
                    GTK_EVENT_CONTROLLER(gesture));
                auto* d = static_cast<TodoItemData*>(
                    g_object_get_data(G_OBJECT(w), "item-data"));
                double cy_s = (Theme::ITEM_H - Theme::CB_SIZE) / 2.0;
                double cy_e = cy_s + Theme::CB_SIZE;
                double cx_e = Theme::CB_PAD_L + Theme::CB_SIZE;
                if (x >= Theme::CB_PAD_L && x <= cx_e &&
                    y >= cy_s            && y <= cy_e) {
                    int id = d->todo.id; App* a = d->app;
                    a->model.toggle(id);
                    a->refresh_list();
                }
            }), nullptr);

        gtk_box_append(GTK_BOX(list_box), area);
    }
}

// ─── Activate ─────────────────────────────────────────────────────────────────

static void on_activate(GtkApplication* gtk_app, gpointer user_data) {
    auto* app = static_cast<App*>(user_data);

    GtkWidget* window = gtk_application_window_new(gtk_app);
    gtk_window_set_title(GTK_WINDOW(window), "ToDo");
    gtk_window_set_default_size(GTK_WINDOW(window), Theme::WIN_W, Theme::WIN_H);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    GtkCssProvider* css = gtk_css_provider_new();
    gtk_css_provider_load_from_data(css, Theme::CSS, -1);
    gtk_style_context_add_provider_for_display(
        gtk_widget_get_display(window),
        GTK_STYLE_PROVIDER(css),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(css);

    GtkWidget* root = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_margin_start(root, Theme::PAD_H);
    gtk_widget_set_margin_end(root, Theme::PAD_H);
    gtk_widget_set_margin_top(root, Theme::PAD_V);
    gtk_widget_set_margin_bottom(root, Theme::PAD_V);
    gtk_window_set_child(GTK_WINDOW(window), root);

    // Title
    GtkWidget* title = gtk_label_new("ToDo");
    gtk_widget_add_css_class(title, "title");
    gtk_widget_set_halign(title, GTK_ALIGN_START);
    gtk_widget_set_margin_bottom(title, 14);
    gtk_box_append(GTK_BOX(root), title);

    // Input
    GtkWidget* input_widget = build_input(app);
    gtk_widget_set_margin_bottom(input_widget, 14);
    gtk_box_append(GTK_BOX(root), input_widget);

    // Tabs
    GtkWidget* tab_widget = build_tabs(app);
    gtk_widget_set_margin_bottom(tab_widget, 3);
    gtk_box_append(GTK_BOX(root), tab_widget);

    // Scrollable list
    GtkWidget* scroll = gtk_scrolled_window_new();
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll),
                                    GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_hexpand(scroll, TRUE);
    gtk_widget_set_vexpand(scroll, TRUE);

    GtkWidget* lbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll), lbox);
    app->list_box = lbox;

    gtk_box_append(GTK_BOX(root), scroll);

    app->refresh_list();
    gtk_widget_show(window);
}

int main(int argc, char** argv) {
    App app;
    GtkApplication* gtk_app = gtk_application_new("com.example.todo.gtk4",
                                                    G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(gtk_app, "activate", G_CALLBACK(on_activate), &app);
    int status = g_application_run(G_APPLICATION(gtk_app), argc, argv);
    g_object_unref(gtk_app);
    return status;
}