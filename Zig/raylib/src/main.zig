const std = @import("std");
const rl = @import("raylib.zig").c;
const th = @import("theme.zig");
const data = @import("data.zig");
const inp_mod = @import("components/input.zig");
const tabs_mod = @import("components/tabs.zig");
const list_mod = @import("components/todo_list.zig");

pub fn main() !void {
    var gpa: std.heap.DebugAllocator(.{}) = .init;
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    var state = try data.AppState.init(allocator);
    defer state.deinit();

    var input = inp_mod.InputState{};
    var scroll: f32 = 0;

    rl.InitWindow(th.WIN_W, th.WIN_H, "ToDo");
    defer rl.CloseWindow();
    rl.SetTargetFPS(60);

    const font = rl.GetFontDefault();
    const bold_font = rl.LoadFontEx("/System/Library/Fonts/Helvetica.ttc", th.NORMAL_FONT_SIZE, null, 0);
    defer rl.UnloadFont(bold_font);

    const content_w: f32 = @as(f32, @floatFromInt(th.WIN_W)) - th.PAD_X * 2;
    const title_h: f32   = @floatFromInt(th.TITLE_FONT_SIZE);

    while (rl.WindowShouldClose() == false) {
        const input_y = th.PAD_Y + title_h + th.MARGIN_TITLE;
        const tabs_y  = input_y + th.INPUT_H + th.MARGIN_INPUT;
        const list_y  = tabs_y + th.TAB_H + th.MARGIN_TAB;
        const list_h  = @as(f32, @floatFromInt(th.WIN_H)) - list_y - th.PAD_Y;

        // Scroll
        const wheel = rl.GetMouseWheelMove();
        if (wheel != 0) {
            const mouse = rl.GetMousePosition();
            const list_rec = rl.Rectangle{ .x = th.PAD_X, .y = list_y, .width = content_w, .height = list_h };
            if (rl.CheckCollisionPointRec(mouse, list_rec)) {
                scroll -= wheel * 30;
                const max_scroll = @max(0, list_mod.totalHeight(&state) - list_h);
                scroll = std.math.clamp(scroll, 0, max_scroll);
            }
        }

        try inp_mod.update(&input, &state, th.PAD_X, input_y, content_w);
        tabs_mod.update(&state, th.PAD_X, tabs_y, font);
        list_mod.update(&state, th.PAD_X, list_y, content_w, list_h, scroll);

        rl.BeginDrawing();
        rl.ClearBackground(th.C_BG);

        // Title
        rl.DrawTextEx(bold_font, "ToDo", .{ .x = th.PAD_X, .y = th.PAD_Y }, @floatFromInt(th.TITLE_FONT_SIZE), 1.0, th.C_WHITE);

        // Input
        inp_mod.draw(&input, th.PAD_X, input_y, content_w);

        // Tabs
        tabs_mod.draw(&state, th.PAD_X, tabs_y, font, bold_font);

        // Todo list
        list_mod.draw(&state, th.PAD_X, list_y, content_w, list_h, scroll, font);

        rl.EndDrawing();
    }
}