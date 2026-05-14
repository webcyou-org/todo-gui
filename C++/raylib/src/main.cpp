#include "raylib.h"
#include "data.h"
#include "theme.h"
#include "draw_helpers.h"
#include "components/input.h"
#include "components/tabs.h"
#include "components/todo_item.h"

Font g_font;

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(800, 600, "ToDo");
    SetTargetFPS(60);

    g_font = GetFontDefault();
    const char* font_paths[] = {
        "/System/Library/Fonts/Helvetica.ttc",
        "/System/Library/Fonts/Supplemental/Arial.ttf",
        nullptr
    };
    for (int i = 0; font_paths[i]; i++) {
        if (FileExists(font_paths[i])) {
            Font f = LoadFontEx(font_paths[i], 32, nullptr, 0);
            if (f.glyphCount > 0) { g_font = f; break; }
        }
    }
    SetTextureFilter(g_font.texture, TEXTURE_FILTER_BILINEAR);

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