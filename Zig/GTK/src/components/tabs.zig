const b = @import("../bindings.zig");
const ctx = @import("../ctx.zig");

pub fn build(click_cb: b.gpointer) b.gpointer {
    const box = b.gtk_box_new(b.GTK_ORIENTATION_HORIZONTAL, 0) orelse return null;
    b.gtk_widget_set_margin_bottom(box, 3);

    const names = [_][*:0]const u8{ "All", "Active", "Completed" };
    for (names, 0..) |name, i| {
        const btn = b.gtk_button_new_with_label(name) orelse return null;
        b.gtk_widget_add_css_class(btn, "tab-btn");
        if (i == 0) b.gtk_widget_add_css_class(btn, "active");
        b.connect(btn, "clicked", click_cb, @ptrFromInt(i));
        b.gtk_box_append(box, btn);
        ctx.G.tab_btns[i] = btn;
    }

    return box;
}