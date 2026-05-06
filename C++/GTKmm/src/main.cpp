#include <gtkmm.h>
#include "data.h"
#include "theme.h"
#include "widgets/todo_input.h"
#include "widgets/tab_menu.h"
#include "widgets/todo_list.h"

class MainWindow : public Gtk::ApplicationWindow {
public:
    MainWindow() {
        set_title("ToDo");
        set_default_size(Theme::WIN_W, Theme::WIN_H);
        set_resizable(false);

        auto css = Gtk::CssProvider::create();
        css->load_from_data(Theme::CSS);
        Gtk::StyleContext::add_provider_for_screen(
            Gdk::Screen::get_default(), css,
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

        outer_.set_margin_start(Theme::PAD_H);
        outer_.set_margin_end(Theme::PAD_H);
        outer_.set_margin_top(Theme::PAD_V);
        outer_.set_margin_bottom(Theme::PAD_V);
        outer_.set_spacing(0);
        add(outer_);

        title_.set_text("ToDo");
        title_.set_halign(Gtk::ALIGN_START);
        title_.get_style_context()->add_class("title");
        outer_.pack_start(title_, false, false, 0);
        outer_.pack_start(*Gtk::make_managed<Gtk::Box>(), false, false, 7);

        input_.signal_submitted.connect(sigc::mem_fun(*this, &MainWindow::on_add_todo));
        outer_.pack_start(input_, false, false, 0);
        outer_.pack_start(*Gtk::make_managed<Gtk::Box>(), false, false, 7);

        tab_menu_.signal_changed.connect(sigc::mem_fun(*this, &MainWindow::on_tab_change));
        outer_.pack_start(tab_menu_, false, false, 0);
        outer_.pack_start(*Gtk::make_managed<Gtk::Box>(), false, false, 3);

        todo_list_.signal_toggle.connect(sigc::mem_fun(*this, &MainWindow::on_toggle));
        outer_.pack_start(todo_list_, true, true, 0);

        refresh_list();
        show_all_children();
    }

private:
    Gtk::Box   outer_{Gtk::ORIENTATION_VERTICAL};
    Gtk::Label title_;
    TodoInput  input_;
    TabMenu    tab_menu_;
    TodoList   todo_list_;
    TodoModel  todo_model_;
    MenuModel  menu_model_;

    void refresh_list() {
        todo_list_.refresh(todo_model_.filtered(menu_model_.active_tab));
    }

    void on_add_todo(const std::string& task) {
        todo_model_.add_todo(task);
        refresh_list();
    }

    void on_tab_change(TabFilter f) {
        menu_model_.active_tab = f;
        refresh_list();
    }

    void on_toggle(int id) {
        todo_model_.toggle(id);
        refresh_list();
    }
};

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create(argc, argv, "com.example.todo");
    MainWindow win;
    return app->run(win);
}