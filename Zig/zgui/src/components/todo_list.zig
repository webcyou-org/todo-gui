const std  = @import("std");
const zgui = @import("zgui");
const data = @import("../data.zig");

inline fn cf(v: comptime_int) f32 { return @as(f32, v) / 255.0; }

const C_SURFACE:   u32 = 0xFF_2A2A2A;
const C_TEXT:      u32 = 0xFF_D2D2D2;
const C_MUTED:     u32 = 0xFF_9B9B9B;
const C_ACCENT:    u32 = 0xFF_AFC25D; // bgr order for imgui u32 color
const C_CB_BORDER: u32 = 0xFF_D9D9D9;

// ImGui color is 0xAABBGGRR
fn col32(r: u8, g: u8, b: u8, a: u8) u32 {
    return @as(u32, a) << 24 | @as(u32, b) << 16 | @as(u32, g) << 8 | @as(u32, r);
}

const BG_COL:   u32 = col32(0x2A, 0x2A, 0x2A, 0xFF);
const TEXT_COL: u32 = col32(0xD2, 0xD2, 0xD2, 0xFF);
const MUTED_COL:u32 = col32(0x9B, 0x9B, 0x9B, 0xFF);
const ACCENT_COL:u32 = col32(0x5D, 0xC2, 0xAF, 0xFF);
const CB_BORDER:u32 = col32(0xD9, 0xD9, 0xD9, 0xFF);

pub fn update(state: *data.AppState) void {
    const avail_h = zgui.getContentRegionAvail()[1];
    _ = zgui.beginChild("##todolist", .{
        .w = 0,
        .h = avail_h,
        .window_flags = .{ .no_scrollbar = false },
    });
    defer zgui.endChild();

    var id_buf: [32]u8 = undefined;

    for (state.todos.items) |todo| {
        if (!state.matches(todo)) continue;

        const id_z = std.fmt.bufPrintZ(&id_buf, "##item_{d}", .{todo.id}) catch continue;

        const dl   = zgui.getWindowDrawList();
        const pos  = zgui.getCursorScreenPos();
        const avail_w = zgui.getContentRegionAvail()[0];
        const h    = 35.0;
        const pad  = 10.0;
        const cb_r = 8.0;
        const cb_margin = 18.0;

        // Reserve row hit area
        _ = zgui.invisibleButton(id_z, .{ .w = avail_w, .h = h });
        const clicked = zgui.isItemClicked(.left);
        const mouse_pos = zgui.getMousePos();

        // Background
        dl.addRectFilled(.{
            .pmin = pos,
            .pmax = .{ pos[0] + avail_w, pos[1] + h },
            .col  = BG_COL,
            .rounding = 4,
        });

        // Circular checkbox
        const cb_cx = pos[0] + pad + cb_r;
        const cb_cy = pos[1] + h / 2.0;
        if (todo.is_completed) {
            dl.addCircle(.{
                .p   = .{ cb_cx, cb_cy },
                .r   = cb_r,
                .col = CB_BORDER,
                .num_segments = 32,
                .thickness = 2,
            });
            dl.addLine(.{ .p1 = .{ cb_cx - 4.0, cb_cy },       .p2 = .{ cb_cx - 1.0, cb_cy + 3.0 }, .col = ACCENT_COL, .thickness = 1.5 });
            dl.addLine(.{ .p1 = .{ cb_cx - 1.0, cb_cy + 3.0 }, .p2 = .{ cb_cx + 4.0, cb_cy - 3.0 }, .col = ACCENT_COL, .thickness = 1.5 });
        } else {
            dl.addCircle(.{
                .p   = .{ cb_cx, cb_cy },
                .r   = cb_r,
                .col = CB_BORDER,
                .num_segments = 32,
                .thickness = 2,
            });
        }

        // Task text
        const text_x = pos[0] + pad + cb_r * 2.0 + cb_margin;
        const font_h = zgui.getFontSize();
        const text_y = pos[1] + (h - font_h) / 2.0;
        const tc     = if (todo.is_completed) MUTED_COL else TEXT_COL;
        dl.addTextUnformatted(.{ text_x, text_y }, tc, todo.task);

        // Strikethrough
        if (todo.is_completed) {
            const tw = zgui.calcTextSize(todo.task, .{})[0];
            const line_y = text_y + font_h * 0.5;
            dl.addLine(.{
                .p1  = .{ text_x, line_y },
                .p2  = .{ text_x + tw, line_y },
                .col = tc,
                .thickness = 1,
            });
        }

        // Hit test: click on checkbox area
        if (clicked) {
            const dx = mouse_pos[0] - cb_cx;
            const dy = mouse_pos[1] - cb_cy;
            const hit_r = cb_r + 6.0;
            if (dx * dx + dy * dy <= hit_r * hit_r) {
                state.toggleCompleted(todo.id);
            }
        }

        zgui.dummy(.{ .w = 0, .h = 2 });
    }
}