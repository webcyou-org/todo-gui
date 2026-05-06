#include "todo_list.h"
#include "../theme.h"
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <algorithm>

int TodoList::totalH() const {
    return (int)m_todos.size() * (Theme::ITEM_H + Theme::ITEM_MB);
}

int TodoList::maxScroll() const {
    int excess = totalH() - h();
    return excess > 0 ? excess : 0;
}

void TodoList::drawItem(const Todo& todo, int iy) {
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

void TodoList::draw() {
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

int TodoList::handle(int event) {
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

TodoList::TodoList(int x, int y, int w, int h, std::function<void(int)> cb)
    : Fl_Widget(x, y, w, h), m_onToggle(std::move(cb)) {}

void TodoList::refresh(const std::vector<Todo>& todos) {
    m_todos   = todos;
    m_scrollY = 0;
    redraw();
}