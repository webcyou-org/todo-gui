#pragma once
#include <gtk/gtk.h>
#include <pango/pangocairo.h>
#include <cmath>
#include "../data.h"
#include "../theme.h"
#include "../cairo_util.h"

struct App;

struct TodoItemData { Todo todo; App* app; };

void draw_todo_item(GtkDrawingArea* area, cairo_t* cr,
                    int width, int height, gpointer user_data);