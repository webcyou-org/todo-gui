const std = @import("std");
const rl = @import("raylib.zig").c;
const th = @import("theme.zig");
const data = @import("data.zig");
const inp_mod = @import("components/input.zig");
const tabs_mod = @import("components/tabs.zig");
const list_mod = @import("components/todo_list.zig");

extern fn ime_setup() void;
extern fn ime_set_cursor(x: f32, y: f32, h: f32) void;
extern fn ime_tick() void;

pub fn main() !void {
    var gpa: std.heap.DebugAllocator(.{}) = .init;
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    var state = try data.AppState.init(allocator);
    defer state.deinit();

    var input = inp_mod.InputState{};
    var scroll: f32 = 0;

    rl.SetConfigFlags(rl.FLAG_WINDOW_HIGHDPI | rl.FLAG_MSAA_4X_HINT);
    rl.InitWindow(th.WIN_W, th.WIN_H, "ToDo");
    defer rl.CloseWindow();
    rl.SetTargetFPS(60);
    ime_setup();

    // Load fonts at 2x size for HiDPI-quality texture atlas, then render at actual size.
    // GetWindowScaleDPI returns the display scale (2.0 on Retina, 1.0 on standard).
    const dpi_scale = rl.GetWindowScaleDPI();
    const scale: f32 = if (dpi_scale.x > 1.0) dpi_scale.x else 1.0;
    const font_size_px:  c_int = @intFromFloat(@as(f32, @floatFromInt(th.LIST_FONT_SIZE))   * scale);
    const ui_size_px:    c_int = @intFromFloat(@as(f32, @floatFromInt(th.NORMAL_FONT_SIZE)) * scale);
    const bold_size_px:  c_int = @intFromFloat(@as(f32, @floatFromInt(th.TITLE_FONT_SIZE))  * scale);

    // Build codepoint list: ASCII + Japanese punctuation + hiragana + katakana + CJK
    var codepoints: std.ArrayList(c_int) = .empty;
    defer codepoints.deinit(allocator);
    {
        var cp: c_int = 32;
        while (cp < 127)    : (cp += 1) try codepoints.append(allocator, cp);
        cp = 0x3000;
        while (cp <= 0x303F): (cp += 1) try codepoints.append(allocator, cp);
        cp = 0x3040;
        while (cp <= 0x309F): (cp += 1) try codepoints.append(allocator, cp);
        cp = 0x30A0;
        while (cp <= 0x30FF): (cp += 1) try codepoints.append(allocator, cp);
        cp = 0x4E00;
        while (cp <= 0x9FFF): (cp += 1) try codepoints.append(allocator, cp);
    }

    const font = rl.LoadFontEx("fonts/NotoSansJP-Medium.ttf", font_size_px, codepoints.items.ptr, @intCast(codepoints.items.len));
    defer rl.UnloadFont(font);
    rl.SetTextureFilter(font.texture, rl.TEXTURE_FILTER_BILINEAR);

    // Inter Medium for UI-only Latin elements (tabs, placeholder)
    const inter_font = rl.LoadFontEx("fonts/Inter-Medium.ttf", ui_size_px, null, 0);
    defer rl.UnloadFont(inter_font);
    rl.SetTextureFilter(inter_font.texture, rl.TEXTURE_FILTER_BILINEAR);

    const bold_font = rl.LoadFontEx("fonts/InterBold.ttf", bold_size_px, null, 0);
    defer rl.UnloadFont(bold_font);
    rl.SetTextureFilter(bold_font.texture, rl.TEXTURE_FILTER_BILINEAR);

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

        // IME tick before input processing so committed chars are in the queue
        if (input.focused) {
            const fs: f32 = @floatFromInt(th.NORMAL_FONT_SIZE);
            const text_w = rl.MeasureTextEx(font, &input.buf, fs, 1.0).x;
            ime_set_cursor(th.PAD_X + 16 + text_w, input_y + (th.INPUT_H - fs) / 2.0, fs);
        }
        ime_tick();

        try inp_mod.update(&input, &state, th.PAD_X, input_y, content_w);
        tabs_mod.update(&state, th.PAD_X, tabs_y, inter_font);
        list_mod.update(&state, th.PAD_X, list_y, content_w, list_h, scroll);

        rl.BeginDrawing();
        rl.ClearBackground(th.C_BG);

        // Title
        rl.DrawTextEx(bold_font, "ToDo", .{ .x = th.PAD_X, .y = th.PAD_Y }, @floatFromInt(th.TITLE_FONT_SIZE), 1.0, th.C_WHITE);

        // Input
        inp_mod.draw(&input, th.PAD_X, input_y, content_w, font, inter_font);

        // Tabs
        tabs_mod.draw(&state, th.PAD_X, tabs_y, inter_font, bold_font);

        // Todo list
        list_mod.draw(&state, th.PAD_X, list_y, content_w, list_h, scroll, font);

        rl.EndDrawing();
    }
}