const std = @import("std");
const b = @import("bindings.zig");
const ctx = @import("ctx.zig");
const data = @import("data.zig");
const input = @import("components/input.zig");
const tabs = @import("components/tabs.zig");
const list = @import("components/todo_list.zig");

// ── CSS ────────────────────────────────────────────────────────────────────────

const CSS =
    \\window.background { background-color: #1C1C1C; }
    \\box { background-color: transparent; }
    \\scrolledwindow viewport { background-color: transparent; }
    \\.app-title { color: #FFFFFF; font-size: 18px; font-weight: bold; }
    \\entry {
    \\  background-color: #303030; color: #FFFFFF;
    \\  border: 1px solid transparent; border-radius: 4px;
    \\  min-height: 35px; padding: 4px 16px; font-size: 14px;
    \\  caret-color: #FFFFFF;
    \\}
    \\entry:focus { border-color: #5DC2AF; }
    \\entry > placeholder { color: #9B9B9B; }
    \\.tab-btn {
    \\  background: transparent; background-image: none;
    \\  border: none; box-shadow: none;
    \\  color: #D2D2D2; font-size: 14px;
    \\  padding: 0 8px; min-height: 28px; border-radius: 0;
    \\}
    \\.tab-btn:hover { background-color: rgba(255,255,255,0.05); }
    \\.tab-btn.active { font-weight: bold; }
    \\.todo-item {
    \\  background-color: #2A2A2A; border-radius: 4px;
    \\  min-height: 35px; padding: 10px; margin-bottom: 5px;
    \\}
    \\.todo-text { color: #D2D2D2; font-size: 14px; }
    \\.todo-text.completed { color: #9B9B9B; text-decoration-line: line-through; }
    \\drawingarea { background-color: transparent; }
;

// ── Signal callbacks ──────────────────────────────────────────────────────────

export fn todo_onEntryActivate(entry: b.gpointer, _: b.gpointer) void {
    const raw = b.gtk_editable_get_text(entry);
    const text = std.mem.trim(u8, std.mem.span(raw), " \t\n\r");
    if (text.len == 0) return;
    ctx.G.state.add(text);
    b.gtk_editable_set_text(entry, "");
    list.rebuild();
}

export fn todo_onTabClicked(_btn: b.gpointer, ud: b.gpointer) void {
    _ = _btn;
    const idx = @as(usize, @intFromPtr(ud));
    ctx.G.state.tab = switch (idx) {
        0 => data.TabFilter.All,
        1 => data.TabFilter.Active,
        2 => data.TabFilter.Completed,
        else => data.TabFilter.All,
    };
    for (&ctx.G.tab_btns, 0..) |*slot, i| {
        const btn = slot.* orelse continue;
        if (i == idx) b.gtk_widget_add_css_class(btn, "active")
        else b.gtk_widget_remove_css_class(btn, "active");
    }
    list.rebuild();
}

// ── App activation ─────────────────────────────────────────────────────────────

export fn todo_onActivate(app: b.gpointer, _: b.gpointer) void {
    // CSS provider
    const prov = b.gtk_css_provider_new();
    b.gtk_css_provider_load_from_string(prov, CSS);
    b.gtk_style_context_add_provider_for_display(
        b.gdk_display_get_default(),
        prov,
        b.GTK_STYLE_PROVIDER_PRIORITY_APPLICATION,
    );
    b.g_object_unref(prov);

    // Window
    const win = b.gtk_application_window_new(app) orelse return;
    b.gtk_window_set_title(win, "ToDo");
    b.gtk_window_set_default_size(win, 800, 600);

    // Root vertical box
    const root = b.gtk_box_new(b.GTK_ORIENTATION_VERTICAL, 0) orelse return;
    b.gtk_widget_set_margin_top(root, 10);
    b.gtk_widget_set_margin_bottom(root, 10);
    b.gtk_widget_set_margin_start(root, 24);
    b.gtk_widget_set_margin_end(root, 24);

    // Title label
    const title = b.gtk_label_new("ToDo") orelse return;
    b.gtk_label_set_xalign(title, 0.0);
    b.gtk_widget_set_margin_bottom(title, 14);
    b.gtk_widget_add_css_class(title, "app-title");

    // Input field
    const entry_widget = input.build(@ptrCast(@constCast(&todo_onEntryActivate))) orelse return;
    ctx.G.entry = entry_widget;

    // Tab menu
    const tabs_widget = tabs.build(@ptrCast(@constCast(&todo_onTabClicked))) orelse return;

    // Scrolled window + list box
    const scroll = b.gtk_scrolled_window_new() orelse return;
    b.gtk_widget_set_vexpand(scroll, 1);
    b.gtk_scrolled_window_set_policy(scroll, b.GTK_POLICY_NEVER, b.GTK_POLICY_AUTOMATIC);

    const lb = b.gtk_box_new(b.GTK_ORIENTATION_VERTICAL, 0) orelse return;
    b.gtk_widget_set_margin_top(lb, 2);
    b.gtk_scrolled_window_set_child(scroll, lb);
    ctx.G.list_box = lb;

    // Assemble
    b.gtk_box_append(root, title);
    b.gtk_box_append(root, entry_widget);
    b.gtk_box_append(root, tabs_widget);
    b.gtk_box_append(root, scroll);
    b.gtk_window_set_child(win, root);

    list.rebuild();
    b.gtk_window_present(win);
}

// ── Entry point ────────────────────────────────────────────────────────────────

pub fn main() void {
    ctx.G = .{
        .state = undefined,
        .list_box = null,
        .entry = null,
        .tab_btns = .{ null, null, null },
    };
    ctx.G.state.init();

    const app = b.gtk_application_new(
        "com.example.todo-gtk",
        b.G_APPLICATION_DEFAULT_FLAGS,
    ) orelse {
        std.debug.print("Failed to create GtkApplication\n", .{});
        return;
    };
    defer b.g_object_unref(app);

    b.connect(app, "activate", @ptrCast(@constCast(&todo_onActivate)), null);
    _ = b.g_application_run(app, 0, null);
}