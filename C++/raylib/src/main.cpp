#include "raylib.h"
#include "data.h"
#include "theme.h"
#include "draw_helpers.h"
#include "components/input.h"
#include "components/tabs.h"
#include "components/todo_item.h"
#include <vector>

Font g_font;       // Inter: Latin/ASCII  — matches design metrics
Font g_font_bold;  // InterBold: title
Font g_font_jp;    // NotoSansJP: hiragana, katakana, fullwidth

// Hiragana + katakana + CJK punctuation + fullwidth forms (no full kanji — atlas too large)
static std::vector<int> buildJpCodepoints() {
    std::vector<int> cp;
    for (int i = 32;     i < 127;    i++) cp.push_back(i);   // ASCII
    for (int i = 0x3000; i <= 0x303F; i++) cp.push_back(i);  // CJK punctuation
    for (int i = 0x3040; i <= 0x309F; i++) cp.push_back(i);  // Hiragana
    for (int i = 0x30A0; i <= 0x30FF; i++) cp.push_back(i);  // Katakana
    for (int i = 0xFF00; i <= 0xFFEF; i++) cp.push_back(i);  // Fullwidth forms (ａｂｃ…)
    return cp;
}

int main() {
    SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_MSAA_4X_HINT);
    InitWindow(800, 600, "ToDo");
    SetTargetFPS(60);

    // Load fonts at DPI-scaled size so the atlas is crisp on Retina displays.
    // Drawing still uses logical pixel sizes (FONT_NORMAL, FONT_TITLE).
    Vector2 dpi   = GetWindowScaleDPI();
    float   scale = (dpi.x > 1.0f) ? dpi.x : 1.0f;
    int normal_px = (int)(FONT_NORMAL * scale);
    int title_px  = (int)(FONT_TITLE  * scale);

    auto cp  = buildJpCodepoints();
    g_font      = LoadFontEx("fonts/Inter.ttf",              normal_px, nullptr,    0);
    g_font_bold = LoadFontEx("fonts/InterBold.ttf",          title_px,  nullptr,    0);
    g_font_jp   = LoadFontEx("fonts/NotoSansJP-Regular.ttf", normal_px, cp.data(), (int)cp.size());
    if (g_font.glyphCount      == 0) g_font      = GetFontDefault();
    if (g_font_bold.glyphCount == 0) g_font_bold = g_font;
    if (g_font_jp.glyphCount   == 0) g_font_jp   = g_font;
    SetTextureFilter(g_font.texture,      TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(g_font_bold.texture, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(g_font_jp.texture,   TEXTURE_FILTER_BILINEAR);

    AppState state;

    while (!WindowShouldClose()) {
        // ── Layout ────────────────────────────────────────────────
        const float title_y   = PAD_Y;
        const float input_y   = title_y + FONT_TITLE + 14.0f;
        const float tabs_y    = input_y + INPUT_H + 14.0f;
        const float list_y    = tabs_y + TAB_LINE_H + 3.0f;
        const float content_w = 800.0f - PAD_X * 2.0f;
        const float list_h    = 600.0f - list_y - PAD_Y;
        const Rectangle input_rect = {PAD_X, input_y, content_w, INPUT_H};
        const Rectangle list_rect  = {PAD_X, list_y,  content_w, list_h};

        // ── Update ────────────────────────────────────────────────
        UpdateInput(state, input_rect);
        UpdateTabs(state, PAD_X, tabs_y);
        UpdateTodoList(state, list_rect);

        // ── Draw ──────────────────────────────────────────────────
        BeginDrawing();
        ClearBackground(C_BG);

        DrawBoldText("ToDo", {PAD_X, title_y}, FONT_TITLE, C_WHITE);
        DrawInput(state, input_rect);
        DrawTabs(state, PAD_X, tabs_y);
        DrawTodoList(state, list_rect);

        EndDrawing();
    }

    UnloadFont(g_font);
    UnloadFont(g_font_bold);
    if (g_font_jp.texture.id != g_font.texture.id) UnloadFont(g_font_jp);
    CloseWindow();
    return 0;
}