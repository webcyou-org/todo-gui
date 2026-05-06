#include "tab_menu.h"
#include "../theme.h"
#include <FL/fl_draw.H>

void TabMenu::btnCb(Fl_Widget* w, void* data) {
    auto* self = static_cast<TabMenu*>(data);
    for (int i = 0; i < N; i++) {
        if (self->m_btns[i] == w) {
            self->setActive(static_cast<TabFilter>(i));
            if (self->m_onChange) self->m_onChange(static_cast<TabFilter>(i));
            return;
        }
    }
}

void TabMenu::draw() {
    fl_color(Theme::BG);
    fl_rectf(x(), y(), w(), h());
    draw_children();
}

TabMenu::TabMenu(int x, int y, int w, int h, std::function<void(TabFilter)> cb)
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

void TabMenu::setActive(TabFilter f) {
    for (int i = 0; i < N; i++)
        m_btns[i]->labelfont(static_cast<int>(f) == i
                              ? FL_HELVETICA_BOLD : FL_HELVETICA);
    redraw();
}