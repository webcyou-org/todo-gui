#pragma once
#include "raylib.h"
#include <cmath>

extern Font g_font;
extern Font g_font_bold;
extern Font g_font_jp;

// Use NotoSansJP when the text contains any non-ASCII byte (hiragana, katakana, etc.)
static inline bool hasNonAscii(const char* s) {
    for (; *s; ++s) if ((unsigned char)*s > 127) return true;
    return false;
}
static inline Font pickFont(const char* text) {
    return hasNonAscii(text) ? g_font_jp : g_font;
}

inline void DrawBoldText(const char* text, Vector2 pos, float size, Color color) {
    DrawTextEx(g_font_bold, text, pos, size, 1.0f, color);
}

inline void DrawNormText(const char* text, Vector2 pos, float size, Color color) {
    DrawTextEx(pickFont(text), text, pos, size, 1.0f, color);
}

inline float MeasureW(const char* text, float size) {
    return MeasureTextEx(pickFont(text), text, size, 1.0f).x;
}

inline float Roundness(Rectangle r, float px) {
    return (px * 2.0f) / fminf(r.width, r.height);
}