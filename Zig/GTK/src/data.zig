const MAX_TASK = 256;
pub const MAX_TODOS = 128;

pub const TabFilter = enum { All, Active, Completed };

pub const Todo = struct {
    id: u32,
    buf: [MAX_TASK]u8, // always null-terminated
    len: usize,
    is_completed: bool,

    pub fn cstr(self: *const Todo) [*:0]const u8 {
        return @as([*:0]const u8, @ptrCast(&self.buf));
    }
};

pub const AppState = struct {
    todos: [MAX_TODOS]Todo,
    count: usize,
    next_id: u32,
    tab: TabFilter,

    pub fn init(self: *AppState) void {
        self.count = 0;
        self.next_id = 1;
        self.tab = .All;
        self.add("Task 1");
        self.add("Task 2");
        self.todos[1].is_completed = true;
        self.add("Task 3");
        self.add("Task 4");
    }

    pub fn add(self: *AppState, task: []const u8) void {
        if (self.count >= MAX_TODOS) return;
        const n = @min(task.len, MAX_TASK - 1);
        const t = &self.todos[self.count];
        t.id = self.next_id;
        @memset(&t.buf, 0);
        @memcpy(t.buf[0..n], task[0..n]);
        t.len = n;
        t.is_completed = false;
        self.next_id += 1;
        self.count += 1;
    }

    pub fn toggle(self: *AppState, id: u32) void {
        for (self.todos[0..self.count]) |*t| {
            if (t.id == id) { t.is_completed = !t.is_completed; return; }
        }
    }

    pub fn isCompleted(self: *const AppState, id: u32) bool {
        for (self.todos[0..self.count]) |*t| {
            if (t.id == id) return t.is_completed;
        }
        return false;
    }
};