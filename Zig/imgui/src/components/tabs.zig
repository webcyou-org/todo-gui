const app = @cImport(@cInclude("imgui_app.h"));
const data = @import("../data.zig");

pub fn update(state: *data.AppState) void {
    app.app_begin_tab_row();
    if (app.app_draw_tab("All",       state.active_tab == .All))       state.active_tab = .All;
    if (app.app_draw_tab("Active",    state.active_tab == .Active))    state.active_tab = .Active;
    if (app.app_draw_tab("Completed", state.active_tab == .Completed)) state.active_tab = .Completed;
    app.app_end_tab_row();
}