#pragma once
#include "raylib.h"
#include "../data.h"
#include "../theme.h"
#include "../draw_helpers.h"

inline void UpdateInput(AppState& state, Rectangle rect) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        state.input_focused = CheckCollisionPointRec(GetMousePosition(), rect);

    if (!state.input_focused) return;

    int ch;
    while ((ch = GetCharPressed()) > 0)
        if (ch >= 32 && ch < 127) state.input_text += (char)ch;

    if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE))
        if (!state.input_text.empty()) state.input_text.pop_back();

    if (IsKeyPressed(KEY_ENTER)) {
        state.add_todo(state.input_text);
        state.input_text.clear();
    }
}

inline void DrawInput(const AppState& state, Rectangle rect) {
    float rnd = Roundness(rect, 4.0f);
    DrawRectangleRounded(rect, rnd, 8, C_INPUT);
    if (state.input_focused)
        DrawRectangleRoundedLinesEx(rect, rnd, 8, 1.0f, C_ACCENT);

    BeginScissorMode((int)rect.x, (int)rect.y, (int)rect.width, (int)rect.height);

    float tx = rect.x + 16.0f;
    float ty = rect.y + (rect.height - FONT_NORMAL) / 2.0f;

    if (!state.input_text.empty()) {
        DrawNormText(state.input_text.c_str(), {tx, ty}, FONT_NORMAL, C_WHITE);
        if (state.input_focused && (int)(GetTime() * 2) % 2 == 0) {
            float cx = tx + MeasureW(state.input_text.c_str(), FONT_NORMAL) + 1.0f;
            DrawRectangle((int)cx, (int)(ty + 1), 1, (int)(FONT_NORMAL - 2), C_WHITE);
        }
    } else if (state.input_focused) {
        if ((int)(GetTime() * 2) % 2 == 0)
            DrawRectangle((int)tx, (int)(ty + 1), 1, (int)(FONT_NORMAL - 2), C_WHITE);
    } else {
        DrawNormText("Add Task", {tx, ty}, FONT_NORMAL, C_MUTED);
    }

    EndScissorMode();
}