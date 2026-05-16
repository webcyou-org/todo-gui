const std = @import("std");
const rl = @import("../raylib.zig").c;
const th = @import("../theme.zig");
const data = @import("../data.zig");

pub const INPUT_MAX = 256;

pub const InputState = struct {
    buf: [INPUT_MAX]u8 = std.mem.zeroes([INPUT_MAX]u8),
    len: usize = 0,
    focused: bool = false,

    pub fn slice(self: *const InputState) []const u8 {
        return self.buf[0..self.len];
    }

    pub fn clear(self: *InputState) void {
        self.len = 0;
        self.buf = std.mem.zeroes([INPUT_MAX]u8);
    }
};

pub fn draw(inp: *const InputState, x: f32, y: f32, w: f32, font: rl.Font) void {
    const rec = rl.Rectangle{ .x = x, .y = y, .width = w, .height = th.INPUT_H };
    rl.DrawRectangleRounded(rec, th.INPUT_RADIUS / (th.INPUT_H / 2.0), 8, th.C_INPUT);
    if (inp.focused) {
        rl.DrawRectangleRoundedLinesEx(rec, th.INPUT_RADIUS / (th.INPUT_H / 2.0), 8, 1.0, th.C_ACCENT);
    }
    const fs: f32 = @floatFromInt(th.NORMAL_FONT_SIZE);
    const tx = x + 16;
    const ty = y + (th.INPUT_H - fs) / 2.0;
    if (inp.len == 0 and !inp.focused) {
        rl.DrawTextEx(font, "Add Task", .{ .x = tx, .y = ty }, fs, 1.0, th.C_MUTED);
    } else {
        rl.DrawTextEx(font, &inp.buf, .{ .x = tx, .y = ty }, fs, 1.0, th.C_WHITE);
    }
}

pub fn update(inp: *InputState, state: *data.AppState, x: f32, y: f32, w: f32) !void {
    const mouse = rl.GetMousePosition();
    const rec = rl.Rectangle{ .x = x, .y = y, .width = w, .height = th.INPUT_H };
    if (rl.IsMouseButtonPressed(rl.MOUSE_BUTTON_LEFT)) {
        inp.focused = rl.CheckCollisionPointRec(mouse, rec);
    }
    if (!inp.focused) return;
    if (rl.IsKeyPressed(rl.KEY_BACKSPACE) or rl.IsKeyPressedRepeat(rl.KEY_BACKSPACE)) {
        if (inp.len > 0) inp.len -= 1;
        inp.buf[inp.len] = 0;
    }
    if (rl.IsKeyPressed(rl.KEY_ENTER)) {
        try state.addTodo(inp.slice());
        inp.clear();
        return;
    }
    var ch = rl.GetCharPressed();
    while (ch != 0) : (ch = rl.GetCharPressed()) {
        if (ch >= 32 and ch < 127 and inp.len < INPUT_MAX - 1) {
            inp.buf[inp.len] = @intCast(ch);
            inp.len += 1;
        }
    }
}