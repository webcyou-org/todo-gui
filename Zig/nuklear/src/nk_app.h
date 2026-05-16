#pragma once

/* Opaque app handle — keeps SDL/Nuklear types out of Zig's @cImport */
typedef struct NkApp NkApp;

/* Simple color and rect types safe to use from Zig */
typedef struct { unsigned char r, g, b, a; } NkAppColor;
typedef struct { float x, y, w, h; }         NkAppRect;

/* Flags returned by nk_app_edit */
#define NK_APP_EDIT_ACTIVE    (1 << 0)
#define NK_APP_EDIT_COMMITTED (1 << 1)

/* Lifecycle */
NkApp* nk_app_create(int width, int height, const char* title);
void   nk_app_destroy(NkApp* app);
void   nk_app_set_style(NkApp* app);

/* Frame — returns 1 when user closes window */
int  nk_app_poll_events(NkApp* app);
void nk_app_frame_begin(NkApp* app);
void nk_app_frame_end(NkApp* app);
void nk_app_render(NkApp* app);

/* Layout */
void nk_app_row_dynamic(NkApp* app, float h, int cols);
void nk_app_row_static_begin(NkApp* app, float h, int cols);
void nk_app_row_push(NkApp* app, float w);
void nk_app_row_end(NkApp* app);
void nk_app_spacing(NkApp* app, int cols);

/* Widgets */
/* align_left: 1 = left-aligned, 0 = centered */
void nk_app_label_colored(NkApp* app, const char* text, NkAppColor color, int align_left);
int  nk_app_button_label(NkApp* app, const char* text);
/* Returns NK_APP_EDIT_* flags; draws placeholder when empty+inactive */
int  nk_app_edit(NkApp* app, char* buf, int* len, int max_len, const char* placeholder);

/* Groups (scrollable container) */
int  nk_app_group_begin(NkApp* app, const char* id);
void nk_app_group_end(NkApp* app);

/* Custom widget slot — consume next layout slot, return its rect */
NkAppRect nk_app_widget_next(NkApp* app);
/* Visible content area of the current window */
NkAppRect nk_app_content_region(NkApp* app);

/* Draw commands (use after nk_app_widget_next) */
void nk_app_draw_fill_rect(NkApp* app, NkAppRect r, float rounding, NkAppColor color);
void nk_app_draw_fill_circle(NkApp* app, NkAppRect r, NkAppColor color);
void nk_app_draw_stroke_circle(NkApp* app, NkAppRect r, float thickness, NkAppColor color);
void nk_app_draw_text(NkApp* app, NkAppRect r, const char* text, int len, NkAppColor fg);
void nk_app_draw_stroke_line(NkApp* app,
    float x0, float y0, float x1, float y1,
    float thickness, NkAppColor color);

/* Returns 1 if left mouse button was clicked within radius r of (cx,cy) */
int nk_app_mouse_clicked_circle(NkApp* app, float cx, float cy, float r);

/* Font metrics */
float nk_app_text_width(NkApp* app, const char* text, int len);
float nk_app_font_height(NkApp* app);