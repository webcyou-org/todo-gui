const zgui = @import("zgui");
const data  = @import("../data.zig");

const TABS = [_]struct { label: [:0]const u8, filter: data.TabFilter }{
    .{ .label = "All",       .filter = .All       },
    .{ .label = "Active",    .filter = .Active    },
    .{ .label = "Completed", .filter = .Completed },
};

pub fn update(state: *data.AppState) void {
    for (TABS, 0..) |tab, i| {
        if (i > 0) zgui.sameLine(.{});

        const is_active = state.active_tab == tab.filter;
        const text_col: [4]f32 = if (is_active) .{ 1, 1, 1, 1 } else .{ 0.55, 0.55, 0.55, 1 };

        const text_w = zgui.calcTextSize(tab.label, .{});
        const btn_w  = text_w[0] + 16.0;
        const btn_h  = 28.0;

        zgui.pushStyleColor4f(.{ .idx = .text, .c = text_col });
        if (zgui.button(tab.label, .{ .w = btn_w, .h = btn_h })) {
            state.active_tab = tab.filter;
        }
        zgui.popStyleColor(.{ .count = 1 });
    }

    zgui.dummy(.{ .w = 0, .h = 6 });
}