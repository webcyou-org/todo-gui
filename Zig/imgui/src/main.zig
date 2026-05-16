const std = @import("std");
const data     = @import("data.zig");
const inp_mod  = @import("components/input.zig");
const tabs_mod = @import("components/tabs.zig");
const list_mod = @import("components/todo_list.zig");
const app = @cImport(@cInclude("imgui_app.h"));

pub fn main() !void {
    var gpa: std.heap.DebugAllocator(.{}) = .init;
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    var state = try data.AppState.init(allocator);
    defer state.deinit();

    const win = app.app_init(800, 600, "ToDo");
    defer app.app_shutdown(win);

    var input_buf = std.mem.zeroes([256]u8);

    while (!app.app_should_close(win)) {
        app.app_new_frame(win);
        app.app_begin_window();

        app.app_draw_title("ToDo");
        try inp_mod.update(&input_buf, &state);
        tabs_mod.update(&state);
        list_mod.update(&state);

        app.app_end_window();
        app.app_render(win);
    }
}
