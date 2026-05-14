#pragma once
#include <cairo.h>
#include <cmath>
#include "theme.h"

inline void cr_color(cairo_t* cr, Theme::RGB c) {
    cairo_set_source_rgb(cr, c.r, c.g, c.b);
}

inline void cr_rounded_rect(cairo_t* cr, double x, double y,
                              double w, double h, double r) {
    cairo_arc(cr, x+r,   y+r,   r, M_PI,     1.5*M_PI);
    cairo_arc(cr, x+w-r, y+r,   r, 1.5*M_PI, 2.0*M_PI);
    cairo_arc(cr, x+w-r, y+h-r, r, 0,         0.5*M_PI);
    cairo_arc(cr, x+r,   y+h-r, r, 0.5*M_PI, M_PI);
    cairo_close_path(cr);
}