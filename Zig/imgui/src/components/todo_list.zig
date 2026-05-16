const std = @import("std");
const app = @cImport(@cInclude("imgui_app.h"));
const data = @import("../data.zig");

pub fn update(state: *data.AppState) void {
    app.app_begin_todo_list(0);
    for (state.todos.items) |todo| {
        if (!state.matches(todo)) continue;
        var id_buf: [16]u8 = undefined;
        const id_z = std.fmt.bufPrintZ(&id_buf, "{d}", .{todo.id}) catch continue;
        const task_z = std.mem.span(@as([*:0]const u8, @ptrCast(todo.task.ptr)));
        if (app.app_draw_todo_item(id_z.ptr, task_z, todo.is_completed)) {
            state.toggleCompleted(todo.id);
        }
    }
    app.app_end_todo_list();
}