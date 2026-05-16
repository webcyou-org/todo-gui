const std = @import("std");
const app = @cImport(@cInclude("imgui_app.h"));
const data = @import("../data.zig");

pub fn update(buf: *[256]u8, state: *data.AppState) !void {
    if (app.app_draw_input(buf, buf.len)) {
        const task = std.mem.sliceTo(buf, 0);
        try state.addTodo(task);
        @memset(buf, 0);
    }
}