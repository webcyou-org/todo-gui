const std = @import("std");
const rl = @import("../raylib.zig").c;
const th = @import("../theme.zig");
const data = @import("../data.zig");

fn drawItem(todo: data.Todo, x: f32, y: f32, w: f32, font: rl.Font) void {
    const rec = rl.Rectangle{ .x = x, .y = y, .width = w, .height = th.ITEM_H };
    rl.DrawRectangleRounded(rec, th.ITEM_RADIUS / (th.ITEM_H / 2.0), 8, th.C_SURFACE);

    // Circular checkbox
    const cx: f32 = x + 10 + th.CB_SIZE / 2;
    const cy: f32 = y + th.ITEM_H / 2;
    const r_outer = th.CB_SIZE / 2;
    const r_inner = r_outer - 1.5;
    rl.DrawRing(.{ .x = cx, .y = cy }, r_inner, r_outer, 0, 360, 36, th.C_CB_BORDER);
    if (todo.is_completed) {
        rl.DrawLineEx(.{ .x = cx - 4, .y = cy },     .{ .x = cx - 1, .y = cy + 3 }, 2.0, th.C_ACCENT);
        rl.DrawLineEx(.{ .x = cx - 1, .y = cy + 3 }, .{ .x = cx + 4, .y = cy - 3 }, 2.0, th.C_ACCENT);
    }

    // Task text
    const text_x = x + 10 + th.CB_SIZE + th.CB_MARGIN_RIGHT;
    const fs: f32 = @floatFromInt(th.LIST_FONT_SIZE);
    const text_y = y + (th.ITEM_H - fs) / 2.0;
    const color = if (todo.is_completed) th.C_MUTED else th.C_TEXT;

    const task_z: [:0]const u8 = std.mem.span(@as([*:0]const u8, @ptrCast(todo.task.ptr)));
    rl.DrawTextEx(font, task_z, .{ .x = text_x, .y = text_y }, fs, 1.0, color);

    // Strikethrough
    if (todo.is_completed) {
        const text_w = rl.MeasureTextEx(font, task_z, fs, 1.0).x;
        rl.DrawLineEx(
            .{ .x = text_x, .y = y + th.ITEM_H / 2.0 },
            .{ .x = text_x + text_w, .y = y + th.ITEM_H / 2.0 },
            1.0,
            th.C_MUTED,
        );
    }
}

pub fn draw(state: *const data.AppState, x: f32, list_y: f32, w: f32, list_h: f32, scroll: f32, font: rl.Font) void {
    rl.BeginScissorMode(
        @intFromFloat(x),
        @intFromFloat(list_y),
        @intFromFloat(w),
        @intFromFloat(list_h),
    );
    var item_y: f32 = list_y - scroll;
    for (state.todos.items) |todo| {
        if (!state.matches(todo)) continue;
        drawItem(todo, x, item_y, w, font);
        item_y += th.ITEM_H + th.MARGIN_ITEM;
    }
    rl.EndScissorMode();
}

pub fn update(state: *data.AppState, x: f32, list_y: f32, w: f32, list_h: f32, scroll: f32) void {
    const mouse = rl.GetMousePosition();
    if (!rl.IsMouseButtonPressed(rl.MOUSE_BUTTON_LEFT)) return;
    var item_y = list_y - scroll;
    for (state.todos.items) |todo| {
        if (!state.matches(todo)) continue;
        const cb_x = x + 10;
        const rec = rl.Rectangle{ .x = cb_x, .y = item_y, .width = th.CB_SIZE + 4, .height = th.ITEM_H };
        if (rl.CheckCollisionPointRec(mouse, rec)) {
            state.toggleCompleted(todo.id);
        }
        item_y += th.ITEM_H + th.MARGIN_ITEM;
    }
    _ = w;
    _ = list_h;
}

pub fn totalHeight(state: *const data.AppState) f32 {
    var count: f32 = 0;
    for (state.todos.items) |todo| {
        if (state.matches(todo)) count += 1;
    }
    return count * (th.ITEM_H + th.MARGIN_ITEM);
}