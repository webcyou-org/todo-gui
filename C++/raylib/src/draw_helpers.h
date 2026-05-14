#pragma once
#include "raylib.h"
#include <cmath>

extern Font g_font;

inline void DrawBoldText(const char* text, Vector2 pos, float size, Color color) {
    DrawTextEx(g_font, text, pos, size, 1.0f, color);
    DrawTextEx(g_font, text, {pos.x + 0.5f, pos.y}, size, 1.0f, color);
}

inline void DrawNormText(const char* text, Vector2 pos, float size, Color color) {
    DrawTextEx(g_font, text, pos, size, 1.0f, color);
}

inline float MeasureW(const char* text, float size) {
    return MeasureTextEx(g_font, text, size, 1.0f).x;
}

inline float Roundness(Rectangle r, float px) {
    return (px * 2.0f) / fminf(r.width, r.height);
}