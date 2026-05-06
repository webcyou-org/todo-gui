#include "todo_input.h"
#include "../theme.h"
#include "../cairo_util.h"

TodoInput::TodoInput() {
    set_size_request(-1, 35);
    bg_.signal_draw().connect(sigc::mem_fun(*this, &TodoInput::on_draw_bg));
    bg_.set_size_request(-1, 35);
    add(bg_);

    entry_.set_placeholder_text("Add Task");
    entry_.get_style_context()->add_class("todo-entry");
    entry_.set_has_frame(false);
    entry_.set_margin_start(1);
    entry_.set_margin_end(1);
    entry_.set_margin_top(1);
    entry_.set_margin_bottom(1);
    entry_.set_valign(Gtk::ALIGN_FILL);
    entry_.set_halign(Gtk::ALIGN_FILL);
    add_overlay(entry_);

    entry_.signal_activate().connect(sigc::mem_fun(*this, &TodoInput::on_enter));
    entry_.signal_focus_in_event().connect(
        [this](GdkEventFocus*){ bg_.queue_draw(); return false; });
    entry_.signal_focus_out_event().connect(
        [this](GdkEventFocus*){ bg_.queue_draw(); return false; });
}

bool TodoInput::on_draw_bg(const Cairo::RefPtr<Cairo::Context>& cr) {
    int w = get_allocated_width(), h = get_allocated_height();
    set_color(cr, Theme::INPUT);
    rounded_rect(cr, 0, 0, w, h, 4);
    cr->fill();
    if (entry_.has_focus()) {
        set_color(cr, Theme::ACCENT);
        cr->set_line_width(1.0);
        rounded_rect(cr, 0.5, 0.5, w - 1, h - 1, 4);
        cr->stroke();
    }
    return false;
}

void TodoInput::on_enter() {
    auto text = Glib::ustring(entry_.get_text()).raw();
    auto s = text.find_first_not_of(" \t");
    if (s == std::string::npos) return;
    text = text.substr(s, text.find_last_not_of(" \t") - s + 1);
    entry_.set_text("");
    signal_submitted.emit(text);
}