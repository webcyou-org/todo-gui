#pragma once
#include "raylib.h"
#include "../data.h"
#include "../theme.h"
#include "../draw_helpers.h"
#include <algorithm>

static inline void DrawCheckbox(Vector2 center, bool checked) {
    if (checked) {
        DrawCircleV(center, CB_RADIUS, C_ACCENT);
        Vector2 p1 = {center.x - 3.0f, center.y + 0.5f};
        Vector2 p2 = {center.x - 0.5f, center.y + 3.0f};
        Vector2 p3 = {center.x + 3.5f, center.y - 2.5f};
        DrawLineEx(p1, p2, 1.5f, C_WHITE);
        DrawLineEx(p2, p3, 1.5f, C_WHITE);
    } else {
        DrawCircleV(center, CB_RADIUS, C_CB_BORDER);
        DrawCircleV(center, CB_RADIUS - 2.0f, C_SURFACE);
    }
}

inline void UpdateTodoList(AppState& state, Rectangle list_rect) {
    auto filtered = state.get_filtered();

    if (CheckCollisionPointRec(GetMousePosition(), list_rect)) {
        state.scroll_offset -= GetMouseWheelMove() * 40.0f;
        float total_h   = (float)filtered.size() * (ITEM_H + ITEM_MB) - ITEM_MB;
        float max_scroll = std::max(0.0f, total_h - list_rect.height);
        state.scroll_offset = std::clamp(state.scroll_offset, 0.0f, max_scroll);
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse = GetMousePosition();
        float iy = list_rect.y - state.scroll_offset;
        for (const auto& todo : filtered) {
            if (iy + ITEM_H > list_rect.y && iy < list_rect.y + list_rect.height) {
                float cb_cx = list_rect.x + 10.0f + CB_RADIUS;
                float cb_cy = iy + ITEM_H / 2.0f;
                if (CheckCollisionPointCircle(mouse, {cb_cx, cb_cy}, CB_RADIUS + 2.0f))
                    state.toggle_todo(todo.id);
            }
            iy += ITEM_H + ITEM_MB;
        }
    }
}

inline void DrawTodoList(const AppState& state, Rectangle list_rect) {
    auto filtered = state.get_filtered();

    BeginScissorMode((int)list_rect.x, (int)list_rect.y,
                     (int)list_rect.width, (int)list_rect.height);

    float iy = list_rect.y - state.scroll_offset;
    for (const auto& todo : filtered) {
        if (iy + ITEM_H > list_rect.y && iy < list_rect.y + list_rect.height) {
            Rectangle item_rect = {list_rect.x, iy, list_rect.width, ITEM_H};
            DrawRectangleRounded(item_rect, Roundness(item_rect, 4.0f), 8, C_SURFACE);

            float cb_cx = list_rect.x + 10.0f + CB_RADIUS;
            float cb_cy = iy + ITEM_H / 2.0f;
            DrawCheckbox({cb_cx, cb_cy}, todo.is_completed);

            float tx = list_rect.x + 10.0f + CB_SIZE + CB_MR;
            float ty = iy + (ITEM_H - FONT_NORMAL) / 2.0f;
            Color color = todo.is_completed ? C_MUTED : C_TEXT;
            DrawNormText(todo.task.c_str(), {tx, ty}, FONT_NORMAL, color);

            if (todo.is_completed) {
                float tw = MeasureW(todo.task.c_str(), FONT_NORMAL);
                float ly = ty + FONT_NORMAL / 2.0f;
                DrawLineEx({tx, ly}, {tx + tw, ly}, 1.0f, C_MUTED);
            }
        }
        iy += ITEM_H + ITEM_MB;
    }

    EndScissorMode();
}