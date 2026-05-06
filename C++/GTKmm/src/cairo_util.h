#pragma once
#include <cairomm/context.h>
#include "theme.h"
#include <cmath>

inline void rounded_rect(const Cairo::RefPtr<Cairo::Context>& cr,
                         double x, double y, double w, double h, double r) {
    cr->arc(x + r,     y + r,     r, M_PI,       1.5 * M_PI);
    cr->arc(x + w - r, y + r,     r, 1.5 * M_PI, 2.0 * M_PI);
    cr->arc(x + w - r, y + h - r, r, 0,           0.5 * M_PI);
    cr->arc(x + r,     y + h - r, r, 0.5 * M_PI,  M_PI);
    cr->close_path();
}

inline void set_color(const Cairo::RefPtr<Cairo::Context>& cr, Theme::RGB c) {
    cr->set_source_rgb(c.r, c.g, c.b);
}