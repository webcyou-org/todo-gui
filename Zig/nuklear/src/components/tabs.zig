const std   = @import("std");
const data  = @import("../data.zig");
const c     = @import("../nk.zig").c;

const C_WHITE = c.NkAppColor{ .r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xFF };

const LABELS  = [_][*:0]const u8{ "All", "Active", "Completed" };
const FILTERS = [_]data.TabFilter{ .All, .Active, .Completed };

pub fn draw(app: *c.NkApp, state: *data.AppState) void {
    c.nk_app_row_static_begin(app, 28, LABELS.len);
    inline for (LABELS, 0..) |label, i| {
        const is_active = state.active_tab == FILTERS[i];
        const text_w = c.nk_app_text_width(app, label, @intCast(std.mem.len(label)));
        c.nk_app_row_push(app, text_w + 16.0);
        if (is_active) {
            c.nk_app_label_colored(app, label, C_WHITE, 0);
        } else {
            if (c.nk_app_button_label(app, label) != 0) {
                state.active_tab = FILTERS[i];
            }
        }
    }
    c.nk_app_row_end(app);

    c.nk_app_row_dynamic(app, 3, 1);
    c.nk_app_spacing(app, 1);
}