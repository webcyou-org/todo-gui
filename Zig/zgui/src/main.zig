const std  = @import("std");
const zgui = @import("zgui");
const data     = @import("data.zig");
const inp_mod  = @import("components/input.zig");
const tabs_mod = @import("components/tabs.zig");
const list_mod = @import("components/todo_list.zig");

const glfw = @cImport({
    @cDefine("GL_SILENCE_DEPRECATION", {});
    @cInclude("GLFW/glfw3.h");
});
const gl = @cImport({
    @cDefine("GL_SILENCE_DEPRECATION", {});
    @cInclude("OpenGL/gl3.h");
});

// ─── bypass zgui's broken @ptrCast(?[:0]const u8) on Zig 0.16.0 ───
extern fn ime_setup_window(glfwwin: *anyopaque) void;
extern fn ime_drain_runloop() void;
extern fn ImGui_ImplGlfw_InitForOpenGL(window: *anyopaque, install_callbacks: bool) bool;
extern fn ImGui_ImplOpenGL3_Init(glsl_version: ?[*:0]const u8) bool;
extern fn ImGui_ImplGlfw_Shutdown() void;
extern fn ImGui_ImplOpenGL3_Shutdown() void;
extern fn ImGui_ImplGlfw_NewFrame() void;
extern fn ImGui_ImplOpenGL3_NewFrame() void;
extern fn ImGui_ImplOpenGL3_RenderDrawData(data_ptr: *anyopaque) void;

const INTER_FONT_PATH = "fonts/Inter.ttf";
const JP_FONT_PATH    = "fonts/NotoSansJP.ttf";
const BOLD_FONT_PATH  = "fonts/InterBold.ttf";

inline fn cf(v: comptime_int) f32 { return @as(f32, v) / 255.0; }

var g_font_title: zgui.Font = undefined;
var g_font_body:  zgui.Font = undefined;

pub fn main() !void {
    var gpa: std.heap.DebugAllocator(.{}) = .init;
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    _ = glfw.glfwInit();
    defer glfw.glfwTerminate();

    glfw.glfwWindowHint(glfw.GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfw.glfwWindowHint(glfw.GLFW_CONTEXT_VERSION_MINOR, 3);
    glfw.glfwWindowHint(glfw.GLFW_OPENGL_PROFILE, glfw.GLFW_OPENGL_CORE_PROFILE);
    glfw.glfwWindowHint(glfw.GLFW_OPENGL_FORWARD_COMPAT, glfw.GL_TRUE);
    glfw.glfwWindowHint(glfw.GLFW_RESIZABLE, glfw.GLFW_FALSE);

    const window = glfw.glfwCreateWindow(800, 600, "ToDo", null, null) orelse return error.GlfwWindow;
    defer glfw.glfwDestroyWindow(window);
    glfw.glfwMakeContextCurrent(window);
    glfw.glfwSwapInterval(1);
    ime_setup_window(window);

    zgui.init(allocator);
    defer zgui.deinit();
    zgui.io.setIniFilename(null);

    // Glyph ranges: pairs of (first, last) codepoints, terminated by 0.
    const jp_glyph_ranges = [_]zgui.Wchar{
        0x0020, 0x00FF, // Basic Latin + Latin supplement
        0x3000, 0x30FF, // CJK symbols, hiragana, katakana
        0x4E00, 0x9FFF, // CJK ideographs
        0,
    };
    // Body: Inter (Latin) base, then merge NotoSansJP for Japanese glyphs
    g_font_body = zgui.io.addFontFromFileWithConfig(INTER_FONT_PATH, 16.0, null, null);
    var merge_cfg = zgui.FontConfig.init();
    merge_cfg.merge_mode = true;
    _ = zgui.io.addFontFromFileWithConfig(JP_FONT_PATH, 16.0, merge_cfg, jp_glyph_ranges[0..].ptr);

    // Title: InterBold for the "ToDo" heading
    g_font_title = zgui.io.addFontFromFileWithConfig(BOLD_FONT_PATH, 18.0, null, null);

    // Init backends directly (workaround for zgui @ptrCast bug on Zig 0.16.0)
    _ = ImGui_ImplGlfw_InitForOpenGL(window, true);
    _ = ImGui_ImplOpenGL3_Init("#version 330 core");
    defer ImGui_ImplGlfw_Shutdown();
    defer ImGui_ImplOpenGL3_Shutdown();

    setupStyle();

    var state = try data.AppState.init(allocator);
    defer state.deinit();

    var input_buf = std.mem.zeroes([256:0]u8);

    while (glfw.glfwWindowShouldClose(window) == 0) {
        ime_drain_runloop();
        glfw.glfwPollEvents();

        var fb_w: c_int = 0;
        var fb_h: c_int = 0;
        glfw.glfwGetFramebufferSize(window, &fb_w, &fb_h);

        var win_w: c_int = 0;
        var win_h: c_int = 0;
        glfw.glfwGetWindowSize(window, &win_w, &win_h);

        // New frame — ImGui_ImplGlfw_NewFrame sets DisplaySize and FramebufferScale correctly
        // for Retina/HiDPI displays, so we must not override them manually.
        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        zgui.newFrame();

        // Main window — use logical pixel size so ImGui coords match mouse coords
        zgui.setNextWindowPos(.{ .x = 0, .y = 0 });
        zgui.setNextWindowSize(.{ .w = @floatFromInt(win_w), .h = @floatFromInt(win_h) });
        _ = zgui.begin("##main", .{
            .flags = .{
                .no_title_bar               = true,
                .no_resize                  = true,
                .no_move                    = true,
                .no_scrollbar               = true,
                .no_scroll_with_mouse       = true,
                .no_bring_to_front_on_focus = true,
            },
        });

        drawTitle();
        try inp_mod.update(&input_buf, &state);
        tabs_mod.update(&state);
        list_mod.update(&state);

        zgui.end();

        // Render
        gl.glViewport(0, 0, fb_w, fb_h);
        gl.glClearColor(cf(0x1C), cf(0x1C), cf(0x1C), 1.0);
        gl.glClear(gl.GL_COLOR_BUFFER_BIT);
        zgui.render();
        ImGui_ImplOpenGL3_RenderDrawData(@ptrCast(zgui.getDrawData()));

        glfw.glfwSwapBuffers(window);
    }
}

fn drawTitle() void {
    zgui.pushFont(g_font_title, 0.0);
    zgui.textColored(.{ 1, 1, 1, 1 }, "ToDo", .{});
    zgui.popFont();
    zgui.dummy(.{ .w = 0, .h = 9 });
}

fn setupStyle() void {
    const style = zgui.getStyle();
    style.window_rounding    = 0;
    style.frame_rounding     = 4;
    style.grab_rounding      = 4;
    style.window_border_size = 0;
    style.window_padding     = .{ 24, 10 };
    style.frame_padding      = .{ 16, 4 };
    style.item_spacing       = .{ 8, 5 };
    style.scrollbar_size     = 8;
    style.scrollbar_rounding = 4;

    style.setColor(.window_bg,              .{ cf(0x1C), cf(0x1C), cf(0x1C), 1 });
    style.setColor(.text,                   .{ cf(0xD2), cf(0xD2), cf(0xD2), 1 });
    style.setColor(.frame_bg,               .{ cf(0x30), cf(0x30), cf(0x30), 1 });
    style.setColor(.frame_bg_hovered,       .{ cf(0x38), cf(0x38), cf(0x38), 1 });
    style.setColor(.frame_bg_active,        .{ cf(0x30), cf(0x30), cf(0x30), 1 });
    style.setColor(.button,                 .{ 0, 0, 0, 0 });
    style.setColor(.button_hovered,         .{ 0.3, 0.3, 0.3, 0.2 });
    style.setColor(.button_active,          .{ 0, 0, 0, 0 });
    style.setColor(.border,                 .{ 0, 0, 0, 0 });
    style.setColor(.scrollbar_bg,           .{ cf(0x1C), cf(0x1C), cf(0x1C), 1 });
    style.setColor(.scrollbar_grab,         .{ cf(0x50), cf(0x50), cf(0x50), 1 });
    style.setColor(.scrollbar_grab_hovered, .{ cf(0x65), cf(0x65), cf(0x65), 1 });
    style.setColor(.scrollbar_grab_active,  .{ cf(0x78), cf(0x78), cf(0x78), 1 });
    style.setColor(.check_mark,             .{ cf(0x5D), cf(0xC2), cf(0xAF), 1 });
}