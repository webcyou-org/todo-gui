#include "raylib.h"
#include "data.h"
#include "theme.h"
#include "draw_helpers.h"
#include "components/input.h"
#include "components/tabs.h"
#include "components/todo_item.h"

Font g_font;
Font g_font_bold;

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(800, 600, "ToDo");
    SetTargetFPS(60);

    g_font      = LoadFontEx("fonts/Inter.ttf",     32, nullptr, 0);
    g_font_bold = LoadFontEx("fonts/InterBold.ttf", 32, nullptr, 0);
    if (g_font.glyphCount == 0)      g_font      = GetFontDefault();
    if (g_font_bold.glyphCount == 0) g_font_bold = g_font;
    SetTextureFilter(g_font.texture,      TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(g_font_bold.texture, TEXTURE_FILTER_BILINEAR);

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

    CloseWindow();
    return 0;
}