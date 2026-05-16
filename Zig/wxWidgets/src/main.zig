const std  = @import("std");
const data = @import("data.zig");
const wx   = @cImport(@cInclude("wx_app.h"));

pub fn main() void {
    var state = data.init();
    wx.wx_run(@ptrCast(&state));
}