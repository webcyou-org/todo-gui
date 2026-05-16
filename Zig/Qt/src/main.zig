const std = @import("std");
const data = @import("data.zig");

// ── C bridge declarations ─────────────────────────────────────────
const CTodo = extern struct {
    id: c_int,
    task: [*:0]const u8,
    is_completed: c_int,
};

const TodoCallbacks = extern struct {
    add_todo:    *const fn ([*:0]const u8) callconv(.c) void,
    toggle_todo: *const fn (c_int) callconv(.c) void,
    set_tab:     *const fn (c_int) callconv(.c) void,
    on_ready:    *const fn () callconv(.c) void,
};

extern fn qt_run(width: c_int, height: c_int, title: [*:0]const u8, cbs: TodoCallbacks) c_int;
extern fn qt_update_todos(todos: [*]const CTodo, count: c_int, active_tab: c_int) void;

// ── global state (accessed from C callbacks) ──────────────────────
var g_state: data.AppState = undefined;

// ── C-linkage callbacks ───────────────────────────────────────────
export fn add_todo_cb(task: [*:0]const u8) callconv(.c) void {
    const slice = std.mem.span(task);
    g_state.addTodo(slice) catch return;
    pushUI();
}

export fn toggle_todo_cb(id: c_int) callconv(.c) void {
    g_state.toggleCompleted(@intCast(id));
    pushUI();
}

export fn set_tab_cb(tab_idx: c_int) callconv(.c) void {
    g_state.active_tab = @enumFromInt(tab_idx);
    pushUI();
}

export fn on_ready_cb() callconv(.c) void {
    pushUI();
}

// ── UI update ─────────────────────────────────────────────────────
fn pushUI() void {
    var c_buf: [256]CTodo = undefined;
    var count: usize = 0;
    for (g_state.todos.items) |todo| {
        if (!g_state.matches(todo)) continue;
        if (count >= c_buf.len) break;
        c_buf[count] = .{
            .id          = @intCast(todo.id),
            .task        = todo.task.ptr,
            .is_completed = if (todo.is_completed) 1 else 0,
        };
        count += 1;
    }
    qt_update_todos(&c_buf, @intCast(count), @intFromEnum(g_state.active_tab));
}

// ── entry point ───────────────────────────────────────────────────
pub fn main() !void {
    var gpa: std.heap.DebugAllocator(.{}) = .init;
    defer _ = gpa.deinit();

    g_state = try data.AppState.init(gpa.allocator());
    defer g_state.deinit();

    _ = qt_run(800, 600, "ToDo", .{
        .add_todo    = add_todo_cb,
        .toggle_todo = toggle_todo_cb,
        .set_tab     = set_tab_cb,
        .on_ready    = on_ready_cb,
    });
}