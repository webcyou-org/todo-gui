const std = @import("std");
const b = @import("../bindings.zig");
const data = @import("../data.zig");
const ctx = @import("../ctx.zig");

// Per-item callback data (heap-allocated, intentionally leaked)
const CbData = struct { id: u32 };

// ── Drawing ────────────────────────────────────────────────────────────────────

export fn todo_drawCb(
    _area: b.gpointer,
    cr: b.gpointer,
    _w: c_int,
    _h: c_int,
    ud: b.gpointer,
) void {
    _ = _area; _ = _w; _ = _h;
    const d: *const CbData = @ptrCast(@alignCast(ud.?));
    const done = ctx.G.state.isCompleted(d.id);

    if (done) {
        // Outlined circle in CB border color
        b.cairo_set_source_rgb(cr, @as(f64, 0xD9)/255.0, @as(f64, 0xD9)/255.0, @as(f64, 0xD9)/255.0);
        b.cairo_arc(cr, 8.0, 8.0, 6.5, 0.0, 2.0 * std.math.pi);
        b.cairo_set_line_width(cr, 1.5);
        b.cairo_stroke(cr);
        // Checkmark in accent
        b.cairo_set_source_rgb(cr, @as(f64, 0x5D)/255.0, @as(f64, 0xC2)/255.0, @as(f64, 0xAF)/255.0);
        b.cairo_new_path(cr);
        b.cairo_move_to(cr, 4.0, 8.0);
        b.cairo_line_to(cr, 7.0, 11.0);
        b.cairo_line_to(cr, 12.0, 5.0);
        b.cairo_set_line_width(cr, 1.5);
        b.cairo_stroke(cr);
    } else {
        b.cairo_set_source_rgb(cr, @as(f64, 0xD9)/255.0, @as(f64, 0xD9)/255.0, @as(f64, 0xD9)/255.0);
        b.cairo_arc(cr, 8.0, 8.0, 6.5, 0.0, 2.0 * std.math.pi);
        b.cairo_set_line_width(cr, 2.0);
        b.cairo_stroke(cr);
    }
}

// ── Gesture ────────────────────────────────────────────────────────────────────

export fn todo_onCbPressed(
    _gest: b.gpointer,
    _n: c_int,
    _x: f64,
    _y: f64,
    ud: b.gpointer,
) void {
    _ = _gest; _ = _n; _ = _x; _ = _y;
    const d: *const CbData = @ptrCast(@alignCast(ud.?));
    ctx.G.state.toggle(d.id);
    rebuild();
}

// ── List rebuild ───────────────────────────────────────────────────────────────

pub fn rebuild() void {
    const lb = ctx.G.list_box orelse return;

    var child = b.gtk_widget_get_first_child(lb);
    while (child) |cur| {
        const nxt = b.gtk_widget_get_next_sibling(cur);
        b.gtk_box_remove(lb, cur);
        child = nxt;
    }

    for (ctx.G.state.todos[0..ctx.G.state.count]) |*todo| {
        const show = switch (ctx.G.state.tab) {
            .All => true,
            .Active => !todo.is_completed,
            .Completed => todo.is_completed,
        };
        if (show) appendItem(todo);
    }
}

fn appendItem(todo: *const data.Todo) void {
    const lb = ctx.G.list_box orelse return;

    const row = b.gtk_box_new(b.GTK_ORIENTATION_HORIZONTAL, 0) orelse return;
    b.gtk_widget_add_css_class(row, "todo-item");
    b.gtk_widget_set_hexpand(row, 1);

    // Circular checkbox (DrawingArea)
    const da = b.gtk_drawing_area_new() orelse return;
    b.gtk_widget_set_size_request(da, 16, 16);
    b.gtk_widget_set_valign(da, b.GTK_ALIGN_CENTER);
    b.gtk_widget_set_margin_end(da, 18);

    const d = std.heap.c_allocator.create(CbData) catch return;
    d.* = .{ .id = todo.id };
    b.gtk_drawing_area_set_draw_func(da, @ptrCast(@constCast(&todo_drawCb)), d, null);

    const gest = b.gtk_gesture_click_new() orelse return;
    b.connect(gest, "pressed", @ptrCast(@constCast(&todo_onCbPressed)), d);
    b.gtk_widget_add_controller(da, gest);

    // Label
    const lbl = b.gtk_label_new(todo.cstr()) orelse return;
    b.gtk_label_set_xalign(lbl, 0.0);
    b.gtk_widget_set_hexpand(lbl, 1);
    b.gtk_widget_add_css_class(lbl, "todo-text");
    if (todo.is_completed) b.gtk_widget_add_css_class(lbl, "completed");

    b.gtk_box_append(row, da);
    b.gtk_box_append(row, lbl);
    b.gtk_box_append(lb, row);
}