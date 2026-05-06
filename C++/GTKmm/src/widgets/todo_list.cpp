#include "todo_list.h"
#include "../theme.h"
#include "../cairo_util.h"
#include <pangomm.h>
#include <cmath>

// ── TodoItemWidget ────────────────────────────────────────────────────────────

TodoItemWidget::TodoItemWidget(const Todo& todo) : todo_(todo) {
    set_size_request(-1, Theme::ITEM_H);
    add_events(Gdk::BUTTON_PRESS_MASK);
}

bool TodoItemWidget::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    int w = get_allocated_width();
    int h = get_allocated_height();

    set_color(cr, Theme::SURFACE);
    rounded_rect(cr, 0, 0, w, h, 4);
    cr->fill();

    double cx  = Theme::CB_PAD_L + Theme::CB_SIZE / 2.0;
    double cy  = h / 2.0;
    double r   = Theme::CB_SIZE / 2.0;

    if (todo_.is_completed) {
        set_color(cr, Theme::ACCENT);
        cr->arc(cx, cy, r, 0, 2 * M_PI);
        cr->fill();
        set_color(cr, Theme::WHITE);
        cr->set_line_width(1.5);
        cr->set_line_cap(Cairo::LINE_CAP_ROUND);
        cr->set_line_join(Cairo::LINE_JOIN_ROUND);
        cr->move_to(cx - 4, cy);
        cr->line_to(cx - 1, cy + 3);
        cr->line_to(cx + 4, cy - 3);
        cr->stroke();
    } else {
        set_color(cr, Theme::CB_BDR);
        cr->set_line_width(2.0);
        cr->arc(cx, cy, r - 1, 0, 2 * M_PI);
        cr->stroke();
    }

    int tx = Theme::CB_PAD_L + Theme::CB_SIZE + Theme::CB_MR;
    set_color(cr, todo_.is_completed ? Theme::MUTED : Theme::TEXT_C);

    auto layout = create_pango_layout(todo_.task);
    layout->set_font_description(Pango::FontDescription("Sans 10"));

    if (todo_.is_completed) {
        auto attr_list = Pango::AttrList();
        auto strike = Pango::Attribute::create_attr_strikethrough(true);
        attr_list.insert(strike);
        layout->set_attributes(attr_list);
    }

    int text_w, text_h;
    layout->get_pixel_size(text_w, text_h);
    cr->move_to(tx, (h - text_h) / 2.0);
    layout->show_in_cairo_context(cr);

    return true;
}

bool TodoItemWidget::on_button_press_event(GdkEventButton* ev) {
    double cx_start = Theme::CB_PAD_L;
    double cx_end   = Theme::CB_PAD_L + Theme::CB_SIZE;
    double cy_start = (Theme::ITEM_H - Theme::CB_SIZE) / 2.0;
    double cy_end   = cy_start + Theme::CB_SIZE;

    if (ev->x >= cx_start && ev->x <= cx_end &&
        ev->y >= cy_start && ev->y <= cy_end) {
        signal_toggle.emit(todo_.id);
    }
    return true;
}

// ── TodoList ──────────────────────────────────────────────────────────────────

TodoList::TodoList() {
    set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
    set_hexpand(true);
    set_vexpand(true);
    vbox_.set_spacing(0);
    add(vbox_);
}

void TodoList::refresh(const std::vector<Todo>& todos) {
    for (auto* w : vbox_.get_children())
        vbox_.remove(*w);
    items_.clear();

    for (const auto& t : todos) {
        auto* item = Gtk::make_managed<TodoItemWidget>(t);
        item->signal_toggle.connect([this](int id){ signal_toggle.emit(id); });
        item->set_margin_bottom(Theme::ITEM_MB);
        vbox_.pack_start(*item, false, false, 0);
        items_.push_back(item);
    }
    vbox_.show_all();
}