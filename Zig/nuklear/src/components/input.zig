const c = @import("../nk.zig").c;

const C_WHITE = c.NkAppColor{ .r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xFF };

pub fn draw(
    app: *c.NkApp,
    buf: *[256]u8,
    len: *c_int,
) bool {
    c.nk_app_row_dynamic(app, 35, 1);
    const result = c.nk_app_edit(app, buf, len, buf.len - 1, "Add Task");

    c.nk_app_row_dynamic(app, 14, 1);
    c.nk_app_spacing(app, 1);

    return (result & c.NK_APP_EDIT_COMMITTED) != 0;
}