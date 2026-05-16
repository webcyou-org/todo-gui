const rl = @import("../raylib.zig").c;
const th = @import("../theme.zig");
const data = @import("../data.zig");

pub const LABELS  = [_][:0]const u8{ "All", "Active", "Completed" };
pub const FILTERS = [_]data.TabFilter{ .All, .Active, .Completed };

pub fn tabWidth(font: rl.Font, label: [:0]const u8) f32 {
    const text_w = rl.MeasureTextEx(font, label, @floatFromInt(th.NORMAL_FONT_SIZE), 1.0).x;
    return text_w + 8 * 2 + 8;
}

pub fn draw(state: *const data.AppState, x: f32, y: f32, font: rl.Font, bold: rl.Font) void {
    var tx: f32 = x;
    for (LABELS, 0..) |label, i| {
        const is_active = state.active_tab == FILTERS[i];
        const fs: f32 = @floatFromInt(th.NORMAL_FONT_SIZE);
        const draw_x = tx + 8;
        const draw_y = y + (th.TAB_H - fs) / 2.0;
        const f = if (is_active) bold else font;
        rl.DrawTextEx(f, label, .{ .x = draw_x, .y = draw_y }, fs, 1.0, th.C_TEXT);
        tx += tabWidth(font, label);
    }
}

pub fn update(state: *data.AppState, x: f32, y: f32, font: rl.Font) void {
    const mouse = rl.GetMousePosition();
    if (!rl.IsMouseButtonPressed(rl.MOUSE_BUTTON_LEFT)) return;
    var tx: f32 = x;
    for (LABELS, 0..) |label, i| {
        const w = tabWidth(font, label);
        const rec = rl.Rectangle{ .x = tx, .y = y, .width = w, .height = th.TAB_H };
        if (rl.CheckCollisionPointRec(mouse, rec)) {
            state.active_tab = FILTERS[i];
        }
        tx += w;
    }
}