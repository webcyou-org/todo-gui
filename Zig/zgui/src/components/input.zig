const std = @import("std");
const zgui = @import("zgui");
const data = @import("../data.zig");

inline fn cf(v: comptime_int) f32 {
    return @as(f32, v) / 255.0;
}

const C_ACCENT: [4]f32 = .{ cf(0x5D), cf(0xC2), cf(0xAF), 1 };
const C_MUTED:  u32    = 0xFF_9B9B9B; // ABGR

var g_was_active: bool = false;

pub fn update(buf: *[256:0]u8, state: *data.AppState) !void {
    const avail = zgui.getContentRegionAvail()[0];
    zgui.setNextItemWidth(avail);

    // Focus border: show accent border when active, transparent otherwise
    const border_col: [4]f32 = if (g_was_active) C_ACCENT else .{ 0, 0, 0, 0 };
    zgui.pushStyleColor4f(.{ .idx = .border, .c = border_col });
    zgui.pushStyleVar1f(.{ .idx = .frame_border_size, .v = 1.0 });
    zgui.pushStyleColor4f(.{ .idx = .text, .c = .{ 1, 1, 1, 1 } });

    const entered = zgui.inputText("##todo_input", .{
        .buf   = buf,
        .flags = .{ .enter_returns_true = true },
    });
    const is_active = zgui.isItemActive();

    // Draw placeholder when empty and not active
    if (!is_active and buf[0] == 0) {
        const dl   = zgui.getWindowDrawList();
        const pmin = zgui.getItemRectMin();
        const pmax = zgui.getItemRectMax();
        const h    = pmax[1] - pmin[1];
        const fh   = zgui.getFontSize();
        dl.addTextUnformatted(
            .{ pmin[0] + 16, pmin[1] + (h - fh) / 2 },
            C_MUTED,
            "Add Task",
        );
    }

    g_was_active = is_active;
    zgui.popStyleColor(.{ .count = 2 });
    zgui.popStyleVar(.{ .count = 1 });

    if (entered) {
        const task = std.mem.sliceTo(buf, 0);
        try state.addTodo(task);
        @memset(buf, 0);
    }

    // margin-bottom: 14px total = 5px (itemSpacing) + 9px dummy
    zgui.dummy(.{ .w = 0, .h = 9 });
}