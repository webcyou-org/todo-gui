const zgui = @import("zgui");
const data  = @import("../data.zig");

const TABS = [_]struct { label: [:0]const u8, filter: data.TabFilter }{
    .{ .label = "All",       .filter = .All       },
    .{ .label = "Active",    .filter = .Active    },
    .{ .label = "Completed", .filter = .Completed },
};

pub fn update(state: *data.AppState, font_body: zgui.Font) void {
    for (TABS, 0..) |tab, i| {
        if (i > 0) zgui.sameLine(.{});

        const is_active = state.active_tab == tab.filter;
        const text_col: [4]f32 = if (is_active) .{ 1, 1, 1, 1 } else .{ 0.82, 0.82, 0.82, 1 };

        const text_w = zgui.calcTextSize(tab.label, .{});
        const btn_w  = text_w[0] + 16.0; // left + right padding 8px each
        const btn_h  = 28.0;

        // Bold for active tab by using the normal font but with a slightly different color
        // (True bold requires a separate bold font; use white color to indicate active)
        if (is_active) {
            // Push body font with larger style to emulate bold (white = active indicator)
            zgui.pushFont(font_body, 14.0);
        }

        zgui.pushStyleColor4f(.{ .idx = .text, .c = text_col });
        if (zgui.button(tab.label, .{ .w = btn_w, .h = btn_h })) {
            state.active_tab = tab.filter;
        }
        zgui.popStyleColor(.{ .count = 1 });

        if (is_active) zgui.popFont();
    }

    zgui.newLine();
    zgui.dummy(.{ .w = 0, .h = 3 }); // TabMenu margin-bottom 3px (already at 0 extra since dummy adds below newLine)
}