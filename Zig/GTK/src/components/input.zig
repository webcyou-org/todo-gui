const b = @import("../bindings.zig");

pub fn build(activate_cb: b.gpointer) b.gpointer {
    const entry = b.gtk_entry_new() orelse return null;
    b.gtk_entry_set_placeholder_text(entry, "Add Task");
    b.gtk_widget_set_hexpand(entry, 1);
    b.gtk_widget_set_margin_bottom(entry, 14);
    b.connect(entry, "activate", activate_cb, null);
    return entry;
}