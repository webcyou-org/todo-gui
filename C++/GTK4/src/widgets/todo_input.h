#pragma once
#include <gtk/gtk.h>
#include <string>
#include "../data.h"
#include "../theme.h"
#include "../cairo_util.h"

struct App;

GtkWidget* build_input(App* app);