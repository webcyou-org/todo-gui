#include "todo_input.h"
#include "../theme.h"
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <cstring>

// ── InnerInput ────────────────────────────────────────────────────────────────

InnerInput::InnerInput(int x, int y, int w, int h) : Fl_Input(x, y, w, h) {}

int InnerInput::handle(int event) {
    int r = Fl_Input::handle(event);
    if (event == FL_FOCUS || event == FL_UNFOCUS)
        parent()->redraw();
    return r;
}

// ── TodoInput ─────────────────────────────────────────────────────────────────

void TodoInput::draw() {
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

TodoInput::TodoInput(int x, int y, int w, int h) : Fl_Group(x, y, w, h) {
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

Fl_Input* TodoInput::input() { return m_input; }