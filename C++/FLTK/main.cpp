#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/fl_draw.H>
#include <cstring>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>

// ────── Theme ──────────────────────────────────────────────────────────────

namespace Theme {
    inline Fl_Color c(uchar r, uchar g, uchar b) { return fl_rgb_color(r, g, b); }

    const Fl_Color BG      = c(0x1C, 0x1C, 0x1C);
    const Fl_Color SURFACE = c(0x2A, 0x2A, 0x2A);
    const Fl_Color INPUT   = c(0x30, 0x30, 0x30);
    const Fl_Color TEXT    = c(0xD2, 0xD2, 0xD2);
    const Fl_Color WHITE   = c(0xFF, 0xFF, 0xFF);
    const Fl_Color MUTED   = c(0x9B, 0x9B, 0x9B);
    const Fl_Color ACCENT  = c(0x5D, 0xC2, 0xAF);
    const Fl_Color CB_BDR  = c(0xD9, 0xD9, 0xD9);

    constexpr int WIN_W  = 800;
    constexpr int WIN_H  = 600;
    constexpr int PAD_H  = 24;
    constexpr int PAD_V  = 10;
    constexpr int CONT_X = PAD_H;
    constexpr int CONT_W = WIN_W - 2 * PAD_H;

    constexpr int TITLE_Y = PAD_V;
    constexpr int TITLE_H = 24;
    constexpr int INPUT_Y = TITLE_Y + TITLE_H + 14;
    constexpr int INPUT_H = 35;
    constexpr int TABS_Y  = INPUT_Y + INPUT_H + 14;
    constexpr int TABS_H  = 28;
    constexpr int LIST_Y  = TABS_Y + TABS_H + 3;
    constexpr int LIST_H  = WIN_H - LIST_Y - PAD_V;

    constexpr int ITEM_H   = 35;
    constexpr int ITEM_MB  = 5;
    constexpr int CB_SIZE  = 16;
    constexpr int CB_PAD_L = 10;
    constexpr int CB_MR    = 18;
    constexpr int LABEL_X  = CB_PAD_L + CB_SIZE + CB_MR;
}

// ────── Data Model ─────────────────────────────────────────────────────────

enum class TabFilter { All, Active, Completed };

struct Todo {
    int         id;
    std::string task;
    bool        isCompleted;
};

class TodoModel {
public:
    TodoModel() {
        sample("Task1", false);
        sample("Task2", true);
        sample("Task3", false);
        sample("Task4", false);
    }

    void addTodo(const std::string& task) {
        m_todos.push_back({ m_nextId++, task, false });
    }

    void toggleCompleted(int id) {
        for (auto& t : m_todos)
            if (t.id == id) { t.isCompleted = !t.isCompleted; return; }
    }

    std::vector<Todo> filteredTodos(TabFilter filter) const {
        if (filter == TabFilter::All) return m_todos;
        std::vector<Todo> out;
        for (const auto& t : m_todos)
            if ((filter == TabFilter::Completed) == t.isCompleted)
                out.push_back(t);
        return out;
    }

private:
    std::vector<Todo> m_todos;
    int               m_nextId = 1;

    void sample(const std::string& task, bool completed) {
        m_todos.push_back({ m_nextId++, task, completed });
    }
};

class MenuModel {
public:
    TabFilter activeTab = TabFilter::All;
};

// ────── TodoInput ──────────────────────────────────────────────────────────

class InnerInput : public Fl_Input {
public:
    InnerInput(int x, int y, int w, int h) : Fl_Input(x, y, w, h) {}

    int handle(int event) override {
        int r = Fl_Input::handle(event);
        if (event == FL_FOCUS || event == FL_UNFOCUS)
            parent()->redraw();
        return r;
    }
};

class TodoInput : public Fl_Group {
    InnerInput* m_input;

    void draw() override {
        bool focused = (Fl::focus() == m_input);
        fl_color(Theme::INPUT);
        fl_rounded_rectf(x(), y(), w(), h(), 4);
        if (focused) {
            fl_color(Theme::ACCENT);
            fl_line_style(FL_SOLID, 1);
            fl_rounded_rect(x(), y(), w(), h(), 4);
            fl_line_style(0);
        }
        draw_children();
        if (std::strlen(m_input->value()) == 0 && !focused) {
            fl_font(FL_HELVETICA, 14);
            fl_color(Theme::MUTED);
            int bline = y() + (h() + fl_height()) / 2 - fl_descent();
            fl_draw("Add Task", x() + 16, bline);
        }
    }

public:
    TodoInput(int x, int y, int w, int h) : Fl_Group(x, y, w, h) {
        box(FL_NO_BOX);
        m_input = new InnerInput(x + 16, y + 1, w - 32, h - 2);
        m_input->box(FL_NO_BOX);
        m_input->color(Theme::INPUT);
        m_input->textcolor(Theme::WHITE);
        m_input->textsize(14);
        m_input->textfont(FL_HELVETICA);
        m_input->cursor_color(Theme::WHITE);
        m_input->when(FL_WHEN_ENTER_KEY);
        end();
    }

    Fl_Input* input() { return m_input; }
};

// ────── TabMenu ────────────────────────────────────────────────────────────

class TabMenu : public Fl_Group {
    static constexpr int N = 3;
    Fl_Button*                     m_btns[N];
    std::function<void(TabFilter)> m_onChange;

    static void btnCb(Fl_Widget* w, void* data) {
        auto* self = static_cast<TabMenu*>(data);
        for (int i = 0; i < N; i++) {
            if (self->m_btns[i] == w) {
                self->setActive(static_cast<TabFilter>(i));
                if (self->m_onChange) self->m_onChange(static_cast<TabFilter>(i));
                return;
            }
        }
    }

    void draw() override {
        fl_color(Theme::BG);
        fl_rectf(x(), y(), w(), h());
        draw_children();
    }

public:
    TabMenu(int x, int y, int w, int h, std::function<void(TabFilter)> cb)
        : Fl_Group(x, y, w, h), m_onChange(std::move(cb))
    {
        box(FL_NO_BOX);
        const char* labels[] = { "All", "Active", "Completed" };
        const int   tab_w[]  = { 48, 70, 108 };
        int cx = x;
        for (int i = 0; i < N; i++) {
            m_btns[i] = new Fl_Button(cx, y, tab_w[i], h, labels[i]);
            m_btns[i]->box(FL_NO_BOX);
            m_btns[i]->color(Theme::BG);
            m_btns[i]->labelcolor(Theme::TEXT);
            m_btns[i]->labelfont(FL_HELVETICA);
            m_btns[i]->labelsize(14);
            m_btns[i]->callback(btnCb, this);
            cx += tab_w[i];
        }
        end();
        setActive(TabFilter::All);
    }

    void setActive(TabFilter f) {
        for (int i = 0; i < N; i++)
            m_btns[i]->labelfont(static_cast<int>(f) == i
                                  ? FL_HELVETICA_BOLD : FL_HELVETICA);
        redraw();
    }
};

// ────── TodoList (custom direct-draw widget) ───────────────────────────────

class TodoList : public Fl_Widget {
    std::vector<Todo>        m_todos;
    std::function<void(int)> m_onToggle;
    int                      m_scrollY = 0;

    int totalH() const {
        return (int)m_todos.size() * (Theme::ITEM_H + Theme::ITEM_MB);
    }

    int maxScroll() const {
        int excess = totalH() - h();
        return excess > 0 ? excess : 0;
    }

    void drawItem(const Todo& todo, int iy) {
        fl_color(Theme::SURFACE);
        fl_rounded_rectf(x(), iy, w(), Theme::ITEM_H, 4);

        int cx = x() + Theme::CB_PAD_L;
        int cy = iy + (Theme::ITEM_H - Theme::CB_SIZE) / 2;
        int cs = Theme::CB_SIZE;

        if (todo.isCompleted) {
            fl_color(Theme::ACCENT);
            fl_pie(cx, cy, cs, cs, 0, 360);
            double ccx = cx + cs / 2.0, ccy = cy + cs / 2.0;
            fl_color(Theme::WHITE);
            fl_line_style(FL_SOLID, 1);
            fl_begin_line();
            fl_vertex(ccx - 4, ccy);
            fl_vertex(ccx - 1, ccy + 3);
            fl_vertex(ccx + 4, ccy - 3);
            fl_end_line();
            fl_line_style(0);
        } else {
            fl_color(Theme::CB_BDR);
            fl_line_style(FL_SOLID, 2);
            fl_arc(cx, cy, cs, cs, 0, 360);
            fl_line_style(0);
        }

        fl_font(FL_HELVETICA, 14);
        fl_color(todo.isCompleted ? Theme::MUTED : Theme::TEXT);
        int tx    = x() + Theme::LABEL_X;
        int bline = iy + (Theme::ITEM_H + fl_height()) / 2 - fl_descent();
        fl_draw(todo.task.c_str(), tx, bline);

        if (todo.isCompleted) {
            double tw = fl_width(todo.task.c_str());
            int    mid = iy + Theme::ITEM_H / 2;
            fl_line_style(FL_SOLID, 1);
            fl_line(tx, mid, tx + (int)tw, mid);
            fl_line_style(0);
        }
    }

    void draw() override {
        fl_push_clip(x(), y(), w(), h());

        fl_color(Theme::BG);
        fl_rectf(x(), y(), w(), h());

        int curr_y = y() - m_scrollY;
        for (const auto& t : m_todos) {
            if (curr_y + Theme::ITEM_H > y() && curr_y < y() + h())
                drawItem(t, curr_y);
            curr_y += Theme::ITEM_H + Theme::ITEM_MB;
        }

        fl_pop_clip();
    }

    int handle(int event) override {
        switch (event) {
            case FL_ENTER:
                Fl::focus(this);
                return 1;
            case FL_PUSH:
                return 1;
            case FL_RELEASE: {
                int mx = Fl::event_x(), my = Fl::event_y();
                int curr_y = y() - m_scrollY;
                for (const auto& t : m_todos) {
                    if (my >= curr_y && my < curr_y + Theme::ITEM_H) {
                        int lx = mx - x();
                        int ly = my - curr_y;
                        int cbx = Theme::CB_PAD_L;
                        int cby = (Theme::ITEM_H - Theme::CB_SIZE) / 2;
                        if (lx >= cbx && lx <= cbx + Theme::CB_SIZE &&
                            ly >= cby && ly <= cby + Theme::CB_SIZE) {
                            if (m_onToggle) m_onToggle(t.id);
                        }
                        return 1;
                    }
                    curr_y += Theme::ITEM_H + Theme::ITEM_MB;
                }
                return 1;
            }
            case FL_MOUSEWHEEL: {
                m_scrollY += Fl::event_dy() * (Theme::ITEM_H + Theme::ITEM_MB);
                m_scrollY = std::max(0, std::min(m_scrollY, maxScroll()));
                redraw();
                return 1;
            }
        }
        return Fl_Widget::handle(event);
    }

public:
    TodoList(int x, int y, int w, int h, std::function<void(int)> cb)
        : Fl_Widget(x, y, w, h), m_onToggle(std::move(cb)) {}

    void refresh(const std::vector<Todo>& todos) {
        m_todos   = todos;
        m_scrollY = 0;
        redraw();
    }
};

// ────── MainWindow ─────────────────────────────────────────────────────────

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

// ────── Main ───────────────────────────────────────────────────────────────

int main(int argc, char** argv) {
    auto* win = new MainWindow();
    win->show(argc, argv);
    return Fl::run();
}