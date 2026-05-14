#pragma once
#include "raylib.h"
#include "../data.h"
#include "../theme.h"
#include "../draw_helpers.h"

struct TabInfo { const char* label; TabFilter filter; };

const TabInfo TABS[]  = {
    {"All",       TabFilter::All},
    {"Active",    TabFilter::Active},
    {"Completed", TabFilter::Completed}
};
const int TAB_CNT = 3;

inline void UpdateTabs(AppState& state, float x, float y) {
    if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) return;
    Vector2 mouse = GetMousePosition();
    float cx = x;
    for (int i = 0; i < TAB_CNT; i++) {
        float w = MeasureW(TABS[i].label, FONT_NORMAL) + 16.0f;
        Rectangle r = {cx, y, w, TAB_LINE_H};
        if (CheckCollisionPointRec(mouse, r)) {
            state.active_tab = TABS[i].filter;
            state.scroll_offset = 0.0f;
        }
        cx += w;
    }
}

inline void DrawTabs(const AppState& state, float x, float y) {
    float cx = x;
    for (int i = 0; i < TAB_CNT; i++) {
        float w  = MeasureW(TABS[i].label, FONT_NORMAL) + 16.0f;
        float ty = y + (TAB_LINE_H - FONT_NORMAL) / 2.0f;
        if (state.active_tab == TABS[i].filter)
            DrawBoldText(TABS[i].label, {cx + 8.0f, ty}, FONT_NORMAL, C_TEXT);
        else
            DrawNormText(TABS[i].label, {cx + 8.0f, ty}, FONT_NORMAL, C_TEXT);
        cx += w;
    }
}