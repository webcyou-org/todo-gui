const std = @import("std");

pub const TabFilter = enum { All, Active, Completed };

pub const Todo = struct {
    id: u32,
    task: []const u8,
    is_completed: bool,
    owned: bool,
};

pub const AppState = struct {
    todos: std.ArrayListUnmanaged(Todo),
    active_tab: TabFilter,
    next_id: u32,
    allocator: std.mem.Allocator,

    pub fn init(allocator: std.mem.Allocator) !AppState {
        var list: std.ArrayListUnmanaged(Todo) = .empty;
        try list.append(allocator, .{ .id = 1, .task = "Task 1", .is_completed = false, .owned = false });
        try list.append(allocator, .{ .id = 2, .task = "Task 2", .is_completed = true,  .owned = false });
        try list.append(allocator, .{ .id = 3, .task = "Task 3", .is_completed = false, .owned = false });
        try list.append(allocator, .{ .id = 4, .task = "Task 4", .is_completed = false, .owned = false });
        return .{ .todos = list, .active_tab = .All, .next_id = 5, .allocator = allocator };
    }

    pub fn deinit(self: *AppState) void {
        for (self.todos.items) |todo| {
            if (todo.owned) self.allocator.free(todo.task);
        }
        self.todos.deinit(self.allocator);
    }

    pub fn addTodo(self: *AppState, task: []const u8) !void {
        if (task.len == 0) return;
        const owned = try self.allocator.dupe(u8, task);
        try self.todos.append(self.allocator, .{
            .id = self.next_id,
            .task = owned,
            .is_completed = false,
            .owned = true,
        });
        self.next_id += 1;
    }

    pub fn toggleCompleted(self: *AppState, id: u32) void {
        for (self.todos.items) |*todo| {
            if (todo.id == id) {
                todo.is_completed = !todo.is_completed;
                return;
            }
        }
    }

    pub fn matches(self: *const AppState, todo: Todo) bool {
        return switch (self.active_tab) {
            .All => true,
            .Active => !todo.is_completed,
            .Completed => todo.is_completed,
        };
    }
};