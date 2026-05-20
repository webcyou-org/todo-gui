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

pub fn draw(inp: *const InputState, x: f32, y: f32, w: f32, font: rl.Font, ui_font: rl.Font) void {
    const rec = rl.Rectangle{ .x = x, .y = y, .width = w, .height = th.INPUT_H };
    rl.DrawRectangleRounded(rec, th.INPUT_RADIUS / (th.INPUT_H / 2.0), 8, th.C_INPUT);
    if (inp.focused) {
        rl.DrawRectangleRoundedLinesEx(rec, th.INPUT_RADIUS / (th.INPUT_H / 2.0), 8, 1.0, th.C_ACCENT);
    }
    const fs: f32 = @floatFromInt(th.NORMAL_FONT_SIZE);
    const tx = x + 16;
    const ty = y + (th.INPUT_H - fs) / 2.0;
    if (inp.len == 0 and !inp.focused) {
        rl.DrawTextEx(ui_font, "Add Task", .{ .x = tx, .y = ty }, fs, 1.0, th.C_MUTED);
    } else {
        rl.DrawTextEx(font, &inp.buf, .{ .x = tx, .y = ty }, fs, 1.0, th.C_WHITE);
    }

    // Blinking cursor
    if (inp.focused) {
        const phase = @mod(rl.GetTime(), 1.0);
        if (phase < 0.5) {
            const text_w: f32 = if (inp.len > 0)
                rl.MeasureTextEx(font, &inp.buf, fs, 1.0).x
            else
                0;
            const cx = tx + text_w + 1;
            rl.DrawLineEx(.{ .x = cx, .y = ty - 1 }, .{ .x = cx, .y = ty + fs + 1 }, 1.5, th.C_WHITE);
        }
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
        // Remove last UTF-8 character by skipping continuation bytes (0x80–0xBF)
        while (inp.len > 0 and (inp.buf[inp.len - 1] & 0xC0) == 0x80) {
            inp.len -= 1;
            inp.buf[inp.len] = 0;
        }
        if (inp.len > 0) {
            inp.len -= 1;
            inp.buf[inp.len] = 0;
        }
    }
    // Process chars BEFORE checking KEY_ENTER:
    // IME commit fires insertText (char) and KEY_ENTER in the same frame.
    // If we check KEY_ENTER first and return, the committed char is discarded.
    var had_chars = false;
    var ch = rl.GetCharPressed();
    while (ch != 0) : (ch = rl.GetCharPressed()) {
        had_chars = true;
        if (ch >= 32) {
            const cp: u21 = @intCast(ch);
            var bytes: [4]u8 = undefined;
            const nbytes: usize = if (cp < 0x80) blk: {
                bytes[0] = @intCast(cp);
                break :blk 1;
            } else if (cp < 0x800) blk: {
                bytes[0] = @intCast(0xC0 | (cp >> 6));
                bytes[1] = @intCast(0x80 | (cp & 0x3F));
                break :blk 2;
            } else if (cp < 0x10000) blk: {
                bytes[0] = @intCast(0xE0 | (cp >> 12));
                bytes[1] = @intCast(0x80 | ((cp >> 6) & 0x3F));
                bytes[2] = @intCast(0x80 | (cp & 0x3F));
                break :blk 3;
            } else blk: {
                bytes[0] = @intCast(0xF0 | (cp >> 18));
                bytes[1] = @intCast(0x80 | ((cp >> 12) & 0x3F));
                bytes[2] = @intCast(0x80 | ((cp >> 6) & 0x3F));
                bytes[3] = @intCast(0x80 | (cp & 0x3F));
                break :blk 4;
            };
            if (inp.len + nbytes < INPUT_MAX) {
                @memcpy(inp.buf[inp.len..inp.len + nbytes], bytes[0..nbytes]);
                inp.len += nbytes;
            }
        }
    }
    // Only submit on Enter if no chars arrived this frame (IME commit sends both)
    if (!had_chars and rl.IsKeyPressed(rl.KEY_ENTER)) {
        try state.addTodo(inp.slice());
        inp.clear();
    }
}