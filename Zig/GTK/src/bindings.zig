// GTK4 / GLib / Cairo manual bindings (no @cImport — avoids translate-c crash)

pub const gpointer = ?*anyopaque;

// ── Constants ─────────────────────────────────────────────────────────────────

pub const GTK_ORIENTATION_HORIZONTAL: c_int = 0;
pub const GTK_ORIENTATION_VERTICAL: c_int = 1;
pub const GTK_ALIGN_CENTER: c_int = 3;
pub const GTK_POLICY_NEVER: c_int = 2;
pub const GTK_POLICY_AUTOMATIC: c_int = 1;
pub const GTK_STYLE_PROVIDER_PRIORITY_APPLICATION: c_uint = 600;
pub const G_APPLICATION_DEFAULT_FLAGS: c_uint = 0;

// ── GObject ────────────────────────────────────────────────────────────────────
pub extern fn g_object_unref(obj: gpointer) void;
pub extern fn g_signal_connect_data(
    instance: gpointer,
    sig: [*:0]const u8,
    handler: gpointer,
    data: gpointer,
    destroy: gpointer,
    flags: c_int,
) c_ulong;

pub fn connect(inst: gpointer, sig: [*:0]const u8, cb: gpointer, data: gpointer) void {
    _ = g_signal_connect_data(inst, sig, cb, data, null, 0);
}

// ── GApplication ──────────────────────────────────────────────────────────────
pub extern fn gtk_application_new(id: [*:0]const u8, flags: c_uint) gpointer;
pub extern fn g_application_run(app: gpointer, argc: c_int, argv: ?[*][*:0]u8) c_int;

// ── GtkWindow ─────────────────────────────────────────────────────────────────
pub extern fn gtk_application_window_new(app: gpointer) gpointer;
pub extern fn gtk_window_set_title(win: gpointer, title: [*:0]const u8) void;
pub extern fn gtk_window_set_default_size(win: gpointer, w: c_int, h: c_int) void;
pub extern fn gtk_window_set_child(win: gpointer, child: gpointer) void;
pub extern fn gtk_window_present(win: gpointer) void;

// ── GtkWidget ─────────────────────────────────────────────────────────────────
pub extern fn gtk_widget_set_hexpand(w: gpointer, v: c_int) void;
pub extern fn gtk_widget_set_vexpand(w: gpointer, v: c_int) void;
pub extern fn gtk_widget_set_margin_top(w: gpointer, v: c_int) void;
pub extern fn gtk_widget_set_margin_bottom(w: gpointer, v: c_int) void;
pub extern fn gtk_widget_set_margin_start(w: gpointer, v: c_int) void;
pub extern fn gtk_widget_set_margin_end(w: gpointer, v: c_int) void;
pub extern fn gtk_widget_set_size_request(w: gpointer, width: c_int, height: c_int) void;
pub extern fn gtk_widget_set_valign(w: gpointer, alignment: c_int) void;
pub extern fn gtk_widget_add_css_class(w: gpointer, cls: [*:0]const u8) void;
pub extern fn gtk_widget_remove_css_class(w: gpointer, cls: [*:0]const u8) void;
pub extern fn gtk_widget_get_first_child(w: gpointer) gpointer;
pub extern fn gtk_widget_get_next_sibling(w: gpointer) gpointer;
pub extern fn gtk_widget_add_controller(w: gpointer, ctrl: gpointer) void;

// ── GtkBox ────────────────────────────────────────────────────────────────────
pub extern fn gtk_box_new(orientation: c_int, spacing: c_int) gpointer;
pub extern fn gtk_box_append(box: gpointer, child: gpointer) void;
pub extern fn gtk_box_remove(box: gpointer, child: gpointer) void;

// ── GtkLabel ──────────────────────────────────────────────────────────────────
pub extern fn gtk_label_new(str: ?[*:0]const u8) gpointer;
pub extern fn gtk_label_set_xalign(label: gpointer, xalign: f32) void;

// ── GtkEntry / GtkEditable ────────────────────────────────────────────────────
pub extern fn gtk_entry_new() gpointer;
pub extern fn gtk_entry_set_placeholder_text(entry: gpointer, text: [*:0]const u8) void;
pub extern fn gtk_editable_get_text(editable: gpointer) [*:0]const u8;
pub extern fn gtk_editable_set_text(editable: gpointer, text: [*:0]const u8) void;

// ── GtkButton ─────────────────────────────────────────────────────────────────
pub extern fn gtk_button_new_with_label(label: [*:0]const u8) gpointer;

// ── GtkDrawingArea ────────────────────────────────────────────────────────────
pub extern fn gtk_drawing_area_new() gpointer;
pub extern fn gtk_drawing_area_set_draw_func(
    da: gpointer,
    func: gpointer,
    data: gpointer,
    destroy: gpointer,
) void;

// ── GtkGestureClick ───────────────────────────────────────────────────────────
pub extern fn gtk_gesture_click_new() gpointer;

// ── GtkScrolledWindow ─────────────────────────────────────────────────────────
pub extern fn gtk_scrolled_window_new() gpointer;
pub extern fn gtk_scrolled_window_set_child(sw: gpointer, child: gpointer) void;
pub extern fn gtk_scrolled_window_set_policy(sw: gpointer, hp: c_int, vp: c_int) void;

// ── CSS / Display ─────────────────────────────────────────────────────────────
pub extern fn gtk_css_provider_new() gpointer;
pub extern fn gtk_css_provider_load_from_string(prov: gpointer, str: [*:0]const u8) void;
pub extern fn gtk_style_context_add_provider_for_display(
    display: gpointer,
    provider: gpointer,
    priority: c_uint,
) void;
pub extern fn gdk_display_get_default() gpointer;

// ── Cairo ─────────────────────────────────────────────────────────────────────
pub extern fn cairo_arc(cr: gpointer, xc: f64, yc: f64, r: f64, a1: f64, a2: f64) void;
pub extern fn cairo_new_path(cr: gpointer) void;
pub extern fn cairo_move_to(cr: gpointer, x: f64, y: f64) void;
pub extern fn cairo_line_to(cr: gpointer, x: f64, y: f64) void;
pub extern fn cairo_set_source_rgb(cr: gpointer, r: f64, g2: f64, b: f64) void;
pub extern fn cairo_set_line_width(cr: gpointer, w: f64) void;
pub extern fn cairo_fill(cr: gpointer) void;
pub extern fn cairo_stroke(cr: gpointer) void;