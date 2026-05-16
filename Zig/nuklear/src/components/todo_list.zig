const data = @import("../data.zig");
const c    = @import("../nk.zig").c;

const C_SURFACE   = c.NkAppColor{ .r = 0x2A, .g = 0x2A, .b = 0x2A, .a = 0xFF };
const C_TEXT      = c.NkAppColor{ .r = 0xD2, .g = 0xD2, .b = 0xD2, .a = 0xFF };
const C_MUTED     = c.NkAppColor{ .r = 0x9B, .g = 0x9B, .b = 0x9B, .a = 0xFF };
const C_ACCENT    = c.NkAppColor{ .r = 0x5D, .g = 0xC2, .b = 0xAF, .a = 0xFF };
const C_CB_BORDER = c.NkAppColor{ .r = 0xD9, .g = 0xD9, .b = 0xD9, .a = 0xFF };

fn drawItem(app: *c.NkApp, todo: data.Todo) bool {
    const ITEM_H: f32   = 35;
    const PAD: f32      = 10;
    const CB_R: f32     = 8;
    const CB_MARGIN: f32 = 18;

    c.nk_app_row_dynamic(app, ITEM_H, 1);
    const bounds = c.nk_app_widget_next(app);
    if (bounds.w == 0) return false;

    c.nk_app_draw_fill_rect(app, bounds, 4.0, C_SURFACE);

    const cb_rect = c.NkAppRect{
        .x = bounds.x + PAD,
        .y = bounds.y + (ITEM_H - CB_R * 2.0) / 2.0,
        .w = CB_R * 2.0,
        .h = CB_R * 2.0,
    };
    if (todo.is_completed) {
        c.nk_app_draw_fill_circle(app, cb_rect, C_ACCENT);
    } else {
        c.nk_app_draw_stroke_circle(app, cb_rect, 2.0, C_CB_BORDER);
    }

    const text_x = bounds.x + PAD + CB_R * 2.0 + CB_MARGIN;
    const font_h = c.nk_app_font_height(app);
    const text_rect = c.NkAppRect{
        .x = text_x,
        .y = bounds.y + (ITEM_H - font_h) / 2.0,
        .w = bounds.w - (text_x - bounds.x) - PAD,
        .h = font_h + 2.0,
    };
    const text_color = if (todo.is_completed) C_MUTED else C_TEXT;
    c.nk_app_draw_text(app, text_rect,
        todo.task.ptr, @intCast(todo.task.len), text_color);

    if (todo.is_completed) {
        const text_w = c.nk_app_text_width(app,
            todo.task.ptr, @intCast(todo.task.len));
        const line_y = bounds.y + ITEM_H / 2.0;
        c.nk_app_draw_stroke_line(app,
            text_x, line_y, text_x + text_w, line_y, 1.0, C_MUTED);
    }

    const cb_cx = bounds.x + PAD + CB_R;
    const cb_cy = bounds.y + ITEM_H / 2.0;
    return c.nk_app_mouse_clicked_circle(app, cb_cx, cb_cy, CB_R + 6) != 0;
}

pub fn draw(app: *c.NkApp, state: *data.AppState) void {
    const region  = c.nk_app_content_region(app);
    const used_h: f32 = 18.0 + 14.0 + 35.0 + 14.0 + 28.0 + 3.0;
    const list_h  = region.h - used_h - 10.0;

    c.nk_app_row_dynamic(app, list_h, 1);
    if (c.nk_app_group_begin(app, "##todos") != 0) {
        for (state.todos.items) |todo| {
            if (!state.matches(todo)) continue;
            if (drawItem(app, todo)) {
                state.toggleCompleted(todo.id);
            }
            c.nk_app_row_dynamic(app, 5, 1);
            c.nk_app_spacing(app, 1);
        }
        c.nk_app_group_end(app);
    }
}