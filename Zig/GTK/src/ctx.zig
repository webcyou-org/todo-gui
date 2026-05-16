const data = @import("data.zig");
const b = @import("bindings.zig");

pub const Ctx = struct {
    state: data.AppState,
    list_box: b.gpointer,
    entry: b.gpointer,
    tab_btns: [3]b.gpointer,
};

pub var G: Ctx = undefined;