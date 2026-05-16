#include "nuklear_config.h"
#include <SDL.h>
#include "nuklear.h"
#include "nuklear_sdl_renderer.h"
#include "nk_app.h"
#include <stdlib.h>
#include <string.h>

/* Design tokens */
#define C_BG        nk_rgb(0x1C, 0x1C, 0x1C)
#define C_SURFACE   nk_rgb(0x2A, 0x2A, 0x2A)
#define C_INPUT     nk_rgb(0x30, 0x30, 0x30)
#define C_TEXT      nk_rgb(0xD2, 0xD2, 0xD2)
#define C_WHITE     nk_rgb(0xFF, 0xFF, 0xFF)
#define C_MUTED     nk_rgb(0x9B, 0x9B, 0x9B)
#define C_ACCENT    nk_rgb(0x5D, 0xC2, 0xAF)
#define C_CB_BORDER nk_rgb(0xD9, 0xD9, 0xD9)

struct NkApp {
    SDL_Window*        window;
    SDL_Renderer*      renderer;
    struct nk_context* ctx;
    float              scale; /* HiDPI pixel ratio (physical / logical) */
    int                quit;
};

static struct nk_color to_nk(NkAppColor c) {
    return nk_rgba(c.r, c.g, c.b, c.a);
}

static struct nk_rect to_rect(NkAppRect r) {
    return nk_rect(r.x, r.y, r.w, r.h);
}

/* ── Lifecycle ────────────────────────────────────────────────────── */

NkApp* nk_app_create(int width, int height, const char* title) {
    NkApp* app = (NkApp*)calloc(1, sizeof(NkApp));
    if (!app) return NULL;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0) {
        free(app); return NULL;
    }
    app->window = SDL_CreateWindow(title,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
        SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    if (!app->window) { SDL_Quit(); free(app); return NULL; }

    app->renderer = SDL_CreateRenderer(app->window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!app->renderer) {
        SDL_DestroyWindow(app->window); SDL_Quit(); free(app); return NULL;
    }

    /* On HiDPI / Retina displays the renderer output is larger than the
       logical window size.  Set the logical size so that Nuklear's layout
       coordinates, SDL mouse event coordinates, and SDL_RenderGeometryRaw
       coordinates all live in the same logical space.                      */
    {
        int lw, lh, rw, rh;
        SDL_GetWindowSize(app->window, &lw, &lh);
        SDL_GetRendererOutputSize(app->renderer, &rw, &rh);
        SDL_RenderSetLogicalSize(app->renderer, lw, lh);
        app->scale = (lw > 0) ? (float)rw / (float)lw : 1.0f;
    }

    app->ctx = nk_sdl_init(app->window, app->renderer);

    /* Load a TTF font baked at physical resolution for crisp Retina text.
       Dividing handle.height by scale gives Nuklear the logical pt size so
       layout arithmetic stays in logical pixels.                           */
    {
        struct nk_font_atlas* atlas = NULL;
        nk_sdl_font_stash_begin(&atlas);

        struct nk_font* font = nk_font_atlas_add_from_file(
            atlas,
            "fonts/Inter.ttf",
            14.0f * app->scale,
            NULL);

        nk_sdl_font_stash_end();

        if (font) {
            font->handle.height /= app->scale;
            nk_style_set_font(app->ctx, &font->handle);
        }
    }

    return app;
}

void nk_app_destroy(NkApp* app) {
    if (!app) return;
    nk_sdl_shutdown();
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    SDL_Quit();
    free(app);
}

void nk_app_set_style(NkApp* app) {
    struct nk_style* s = &app->ctx->style;

    s->window.background       = C_BG;
    s->window.fixed_background = nk_style_item_color(C_BG);
    s->window.border           = 0;
    s->window.padding          = nk_vec2(24, 10);
    s->window.spacing          = nk_vec2(0, 0);
    s->window.group_padding    = nk_vec2(0, 0);
    s->window.scrollbar_size   = nk_vec2(8, 8);

    /* Hide title bar by matching its colors to the background */
    s->window.header.normal       = nk_style_item_color(C_BG);
    s->window.header.hover        = nk_style_item_color(C_BG);
    s->window.header.active       = nk_style_item_color(C_BG);
    s->window.header.label_normal = C_BG;
    s->window.header.label_hover  = C_BG;
    s->window.header.label_active = C_BG;
    s->window.header.padding      = nk_vec2(0, 0);
    s->window.header.label_padding = nk_vec2(0, 0);
    s->window.header.spacing      = nk_vec2(0, 0);

    s->text.color = C_TEXT;

    s->edit.normal              = nk_style_item_color(C_INPUT);
    s->edit.hover               = nk_style_item_color(C_INPUT);
    s->edit.active              = nk_style_item_color(C_INPUT);
    s->edit.text_normal         = C_WHITE;
    s->edit.text_hover          = C_WHITE;
    s->edit.text_active         = C_WHITE;
    s->edit.cursor_normal       = C_WHITE;
    s->edit.cursor_hover        = C_WHITE;
    s->edit.cursor_text_normal  = C_INPUT;
    s->edit.cursor_text_hover   = C_INPUT;
    s->edit.selected_normal     = C_ACCENT;
    s->edit.selected_hover      = C_ACCENT;
    s->edit.selected_text_normal = C_WHITE;
    s->edit.selected_text_hover  = C_WHITE;
    s->edit.border              = 1;
    s->edit.rounding            = 4;
    s->edit.cursor_size         = 2;
    s->edit.border_color        = nk_rgba(0, 0, 0, 0);
    s->edit.padding             = nk_vec2(16, 4);

    s->button.normal            = nk_style_item_color(nk_rgba(0, 0, 0, 0));
    s->button.hover             = nk_style_item_color(nk_rgba(0x33, 0x33, 0x33, 0xCC));
    s->button.active            = nk_style_item_color(nk_rgba(0, 0, 0, 0));
    s->button.border_color      = nk_rgba(0, 0, 0, 0);
    s->button.text_normal       = C_TEXT;
    s->button.text_hover        = C_WHITE;
    s->button.text_active       = C_WHITE;
    s->button.border            = 0;
    s->button.rounding          = 0;
    s->button.padding           = nk_vec2(8, 0);

    s->scrollv.normal           = nk_style_item_color(C_BG);
    s->scrollv.hover            = nk_style_item_color(C_BG);
    s->scrollv.active           = nk_style_item_color(C_BG);
    s->scrollv.cursor_normal    = nk_style_item_color(nk_rgb(0x50, 0x50, 0x50));
    s->scrollv.cursor_hover     = nk_style_item_color(nk_rgb(0x65, 0x65, 0x65));
    s->scrollv.cursor_active    = nk_style_item_color(nk_rgb(0x78, 0x78, 0x78));
    s->scrollv.border           = 0;
    s->scrollv.padding          = nk_vec2(0, 0);
}

/* ── Frame ────────────────────────────────────────────────────────── */

int nk_app_poll_events(NkApp* app) {
    SDL_Event event;
    nk_input_begin(app->ctx);
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) app->quit = 1;
        nk_sdl_handle_event(&event);
    }
    nk_input_end(app->ctx);
    return app->quit;
}

void nk_app_frame_begin(NkApp* app) {
    int w, h;
    SDL_GetWindowSize(app->window, &w, &h);
    nk_flags flags = NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_BACKGROUND;
    nk_begin(app->ctx, "##main", nk_rect(0, 0, (float)w, (float)h), flags);
}

void nk_app_frame_end(NkApp* app) {
    nk_end(app->ctx);
}

void nk_app_render(NkApp* app) {
    SDL_SetRenderDrawColor(app->renderer, 0x1C, 0x1C, 0x1C, 0xFF);
    SDL_RenderClear(app->renderer);
    nk_sdl_render(NK_ANTI_ALIASING_ON);
    SDL_RenderPresent(app->renderer);
}

/* ── Layout ───────────────────────────────────────────────────────── */

void nk_app_row_dynamic(NkApp* app, float h, int cols) {
    nk_layout_row_dynamic(app->ctx, h, cols);
}

void nk_app_row_static_begin(NkApp* app, float h, int cols) {
    nk_layout_row_begin(app->ctx, NK_STATIC, h, cols);
}

void nk_app_row_push(NkApp* app, float w) {
    nk_layout_row_push(app->ctx, w);
}

void nk_app_row_end(NkApp* app) {
    nk_layout_row_end(app->ctx);
}

void nk_app_spacing(NkApp* app, int cols) {
    nk_spacing(app->ctx, cols);
}

/* ── Widgets ──────────────────────────────────────────────────────── */

void nk_app_label_colored(NkApp* app, const char* text, NkAppColor color, int align_left) {
    nk_label_colored(app->ctx, text,
        align_left ? NK_TEXT_LEFT : NK_TEXT_CENTERED,
        to_nk(color));
}

int nk_app_button_label(NkApp* app, const char* text) {
    return nk_button_label(app->ctx, text);
}

int nk_app_edit(NkApp* app, char* buf, int* len, int max_len, const char* placeholder) {
    /* Peek at widget bounds before edit consumes the slot */
    struct nk_rect bounds = nk_widget_bounds(app->ctx);

    nk_flags edit_flags = NK_EDIT_FIELD | NK_EDIT_SIG_ENTER | NK_EDIT_NO_HORIZONTAL_SCROLL;
    nk_flags result = nk_edit_string(app->ctx, edit_flags, buf, len, max_len, nk_filter_default);

    /* Draw placeholder when field is empty and not focused */
    if (*len == 0 && !(result & NK_EDIT_ACTIVE) && placeholder) {
        const struct nk_user_font* font = app->ctx->style.font;
        float fh = font->height;
        struct nk_rect ph = nk_rect(
            bounds.x + 16.0f, bounds.y + (bounds.h - fh) / 2.0f,
            bounds.w - 32.0f, fh + 4.0f);
        nk_draw_text(nk_window_get_canvas(app->ctx), ph,
            placeholder, (int)strlen(placeholder),
            font, nk_rgba(0, 0, 0, 0), C_MUTED);
    }

    /* Update border color */
    if (result & NK_EDIT_ACTIVE)
        app->ctx->style.edit.border_color = C_ACCENT;
    else
        app->ctx->style.edit.border_color = nk_rgba(0, 0, 0, 0);

    int out = 0;
    if (result & NK_EDIT_ACTIVE)    out |= NK_APP_EDIT_ACTIVE;
    if (result & NK_EDIT_COMMITED)  out |= NK_APP_EDIT_COMMITTED;
    return out;
}

int nk_app_group_begin(NkApp* app, const char* id) {
    return nk_group_begin(app->ctx, id, 0);
}

void nk_app_group_end(NkApp* app) {
    nk_group_end(app->ctx);
}

/* ── Custom widget ────────────────────────────────────────────────── */

NkAppRect nk_app_widget_next(NkApp* app) {
    struct nk_rect r = {0, 0, 0, 0};
    nk_widget(&r, app->ctx);
    return (NkAppRect){r.x, r.y, r.w, r.h};
}

NkAppRect nk_app_content_region(NkApp* app) {
    struct nk_rect r = nk_window_get_content_region(app->ctx);
    return (NkAppRect){r.x, r.y, r.w, r.h};
}

static struct nk_command_buffer* canvas(NkApp* app) {
    return nk_window_get_canvas(app->ctx);
}

void nk_app_draw_fill_rect(NkApp* app, NkAppRect r, float rounding, NkAppColor color) {
    nk_fill_rect(canvas(app), to_rect(r), rounding, to_nk(color));
}

void nk_app_draw_fill_circle(NkApp* app, NkAppRect r, NkAppColor color) {
    nk_fill_circle(canvas(app), to_rect(r), to_nk(color));
}

void nk_app_draw_stroke_circle(NkApp* app, NkAppRect r, float thickness, NkAppColor color) {
    nk_stroke_circle(canvas(app), to_rect(r), thickness, to_nk(color));
}

void nk_app_draw_text(NkApp* app, NkAppRect r, const char* text, int len, NkAppColor fg) {
    const struct nk_user_font* font = app->ctx->style.font;
    nk_draw_text(canvas(app), to_rect(r), text, len,
        font, nk_rgba(0, 0, 0, 0), to_nk(fg));
}

void nk_app_draw_stroke_line(NkApp* app,
    float x0, float y0, float x1, float y1, float thickness, NkAppColor color)
{
    nk_stroke_line(canvas(app), x0, y0, x1, y1, thickness, to_nk(color));
}

int nk_app_mouse_clicked_circle(NkApp* app, float cx, float cy, float r) {
    /* Match nk_input_is_mouse_released: trigger only on button-up, not button-down */
    struct nk_mouse_button* btn = &app->ctx->input.mouse.buttons[NK_BUTTON_LEFT];
    if (!btn->clicked || btn->down) return 0;
    float dx = app->ctx->input.mouse.pos.x - cx;
    float dy = app->ctx->input.mouse.pos.y - cy;
    return (dx * dx + dy * dy) <= (r * r);
}

/* ── Font metrics ─────────────────────────────────────────────────── */

float nk_app_text_width(NkApp* app, const char* text, int len) {
    const struct nk_user_font* font = app->ctx->style.font;
    return font->width(font->userdata, font->height, text, len);
}

float nk_app_font_height(NkApp* app) {
    return app->ctx->style.font->height;
}