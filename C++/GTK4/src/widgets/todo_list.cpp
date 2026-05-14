#include "todo_list.h"
#include "../app.h"

void draw_todo_item(GtkDrawingArea*, cairo_t* cr,
                    int width, int height, gpointer user_data) {
    auto* d = static_cast<TodoItemData*>(user_data);
    const Todo& t = d->todo;

    cr_color(cr, Theme::SURFACE);
    cr_rounded_rect(cr, 0, 0, width, height, 4.0);
    cairo_fill(cr);

    double cx = Theme::CB_PAD_L + Theme::CB_SIZE / 2.0;
    double cy = height / 2.0;
    double r  = Theme::CB_SIZE / 2.0;

    if (t.is_completed) {
        cr_color(cr, Theme::ACCENT);
        cairo_arc(cr, cx, cy, r, 0, 2 * M_PI);
        cairo_fill(cr);
        cr_color(cr, Theme::WHITE);
        cairo_set_line_width(cr, 1.5);
        cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
        cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);
        cairo_move_to(cr, cx - 4, cy);
        cairo_line_to(cr, cx - 1, cy + 3);
        cairo_line_to(cr, cx + 4, cy - 3);
        cairo_stroke(cr);
    } else {
        cr_color(cr, Theme::CB_BDR);
        cairo_set_line_width(cr, 2.0);
        cairo_arc(cr, cx, cy, r - 1, 0, 2 * M_PI);
        cairo_stroke(cr);
    }

    int tx = Theme::CB_PAD_L + Theme::CB_SIZE + Theme::CB_MR;
    cr_color(cr, t.is_completed ? Theme::MUTED : Theme::TEXT_C);

    PangoLayout* layout = pango_cairo_create_layout(cr);
    pango_layout_set_text(layout, t.task.c_str(), -1);
    PangoFontDescription* fd = pango_font_description_from_string("Sans 10");
    pango_layout_set_font_description(layout, fd);
    pango_font_description_free(fd);

    if (t.is_completed) {
        PangoAttrList* attrs = pango_attr_list_new();
        PangoAttribute* strike = pango_attr_strikethrough_new(TRUE);
        pango_attr_list_insert(attrs, strike);
        pango_layout_set_attributes(layout, attrs);
        pango_attr_list_unref(attrs);
    }

    int tw, th;
    pango_layout_get_pixel_size(layout, &tw, &th);
    cairo_move_to(cr, tx, (height - th) / 2.0);
    pango_cairo_show_layout(cr, layout);
    g_object_unref(layout);
}