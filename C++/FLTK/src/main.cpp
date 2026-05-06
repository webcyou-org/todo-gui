#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include "data.h"
#include "theme.h"
#include "widgets/todo_input.h"
#include "widgets/tab_menu.h"
#include "widgets/todo_list.h"

// ── MainWindow ────────────────────────────────────────────────────────────────

class MainWindow : public Fl_Window {
    TodoModel  m_todoModel;
    MenuModel  m_menuModel;
    TodoInput* m_input    = nullptr;
    TabMenu*   m_tabMenu  = nullptr;
    TodoList*  m_todoList = nullptr;

    static void inputEnterCb(Fl_Widget*, void* data) {
        static_cast<MainWindow*>(data)->onAddTodo();
    }

    void onAddTodo() {
        std::string text = m_input->input()->value();
        auto s = text.find_first_not_of(" \t");
        if (s == std::string::npos) return;
        text = text.substr(s, text.find_last_not_of(" \t") - s + 1);
        m_todoModel.addTodo(text);
        m_input->input()->value("");
        refreshList();
    }

    void onToggle(int id) {
        m_todoModel.toggleCompleted(id);
        refreshList();
    }

    void refreshList() {
        if (m_todoList)
            m_todoList->refresh(m_todoModel.filteredTodos(m_menuModel.activeTab));
    }

    void draw() override {
        fl_color(Theme::BG);
        fl_rectf(0, 0, w(), h());
        draw_children();
    }

public:
    MainWindow() : Fl_Window(Theme::WIN_W, Theme::WIN_H, "ToDo") {
        size_range(Theme::WIN_W, Theme::WIN_H, Theme::WIN_W, Theme::WIN_H);

        auto* title = new Fl_Box(Theme::CONT_X, Theme::TITLE_Y,
                                  Theme::CONT_W, Theme::TITLE_H, "ToDo");
        title->box(FL_NO_BOX);
        title->labelcolor(Theme::WHITE);
        title->labelfont(FL_HELVETICA_BOLD);
        title->labelsize(18);
        title->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);

        m_input = new TodoInput(Theme::CONT_X, Theme::INPUT_Y,
                                 Theme::CONT_W, Theme::INPUT_H);
        m_input->input()->callback(inputEnterCb, this);

        m_tabMenu = new TabMenu(
            Theme::CONT_X, Theme::TABS_Y,
            Theme::CONT_W, Theme::TABS_H,
            [this](TabFilter f) {
                m_menuModel.activeTab = f;
                refreshList();
            }
        );

        m_todoList = new TodoList(
            Theme::CONT_X, Theme::LIST_Y,
            Theme::CONT_W, Theme::LIST_H,
            [this](int id) { onToggle(id); }
        );

        end();
        refreshList();
    }
};

// ── Main ──────────────────────────────────────────────────────────────────────

int main(int argc, char** argv) {
    auto* win = new MainWindow();
    win->show(argc, argv);
    return Fl::run();
}