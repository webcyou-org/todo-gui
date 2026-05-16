#pragma once
#include "imgui.h"
#include "data.h"

void render_todo_input(TodoModel& model, char* buf, int buf_size,
                       bool& needs_focus, ImFont* font_bold_14);
