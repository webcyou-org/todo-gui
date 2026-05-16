const std       = @import("std");
const data      = @import("data.zig");
const input_ui  = @import("components/input.zig");
const tabs_ui   = @import("components/tabs.zig");
const list_ui   = @import("components/todo_list.zig");

const c = @import("nk.zig").c;

const C_WHITE = c.NkAppColor{ .r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xFF };

pub fn main() !void {
    var gpa: std.heap.DebugAllocator(.{}) = .init;
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    var state = try data.AppState.init(allocator);
    defer state.deinit();

    const app = c.nk_app_create(800, 600, "ToDo") orelse return;
    defer c.nk_app_destroy(app);
    c.nk_app_set_style(app);

    var input_buf = std.mem.zeroes([256]u8);
    var input_len: c_int = 0;

    while (c.nk_app_poll_events(app) == 0) {
        c.nk_app_frame_begin(app);

        // Title
        c.nk_app_row_dynamic(app, 18, 1);
        c.nk_app_label_colored(app, "ToDo", C_WHITE, 1);
        c.nk_app_row_dynamic(app, 14, 1);
        c.nk_app_spacing(app, 1);

        // Input
        if (input_ui.draw(app, &input_buf, &input_len)) {
            const task = input_buf[0..@intCast(input_len)];
            try state.addTodo(task);
            input_len = 0;
            @memset(&input_buf, 0);
        }

        // Tabs
        tabs_ui.draw(app, &state);

        // Todo list
        list_ui.draw(app, &state);

        c.nk_app_frame_end(app);
        c.nk_app_render(app);
    }
}