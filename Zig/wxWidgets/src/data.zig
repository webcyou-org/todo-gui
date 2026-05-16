const std = @import("std");

pub const TabFilter = enum(c_int) {
    all       = 0,
    active    = 1,
    completed = 2,
};

pub const Todo = extern struct {
    id:           u32,
    task:         [256]u8,
    is_completed: c_int,
};

pub const AppState = extern struct {
    todos:      [256]Todo,
    todo_count: c_int,
    active_tab: TabFilter,
    next_id:    u32,
};

fn makeTodo(id: u32, task_str: []const u8, completed: bool) Todo {
    var todo = std.mem.zeroes(Todo);
    todo.id           = id;
    todo.is_completed = if (completed) 1 else 0;
    const len = @min(task_str.len, 255);
    @memcpy(todo.task[0..len], task_str[0..len]);
    return todo;
}

pub fn init() AppState {
    var state      = std.mem.zeroes(AppState);
    state.active_tab = .all;
    state.next_id    = 5;

    state.todos[0]   = makeTodo(1, "Task 1", false);
    state.todos[1]   = makeTodo(2, "Task 2", true);
    state.todos[2]   = makeTodo(3, "Task 3", false);
    state.todos[3]   = makeTodo(4, "Task 4", false);
    state.todo_count = 4;

    return state;
}

export fn state_add_todo(state: *AppState, task_ptr: [*:0]const u8) void {
    if (state.todo_count >= 256) return;
    const task = std.mem.span(task_ptr);
    if (task.len == 0) return;

    const idx: usize    = @intCast(state.todo_count);
    state.todos[idx]    = makeTodo(state.next_id, task, false);
    state.next_id      += 1;
    state.todo_count   += 1;
}

export fn state_toggle_todo(state: *AppState, id: u32) void {
    const count: usize = @intCast(state.todo_count);
    for (state.todos[0..count]) |*todo| {
        if (todo.id == id) {
            todo.is_completed = if (todo.is_completed != 0) 0 else 1;
            return;
        }
    }
}

export fn state_set_tab(state: *AppState, tab: TabFilter) void {
    state.active_tab = tab;
}