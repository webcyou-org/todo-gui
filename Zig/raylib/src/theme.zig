const rl = @import("raylib.zig").c;

pub const C_BG        = rl.Color{ .r = 0x1C, .g = 0x1C, .b = 0x1C, .a = 0xFF };
pub const C_SURFACE   = rl.Color{ .r = 0x2A, .g = 0x2A, .b = 0x2A, .a = 0xFF };
pub const C_INPUT     = rl.Color{ .r = 0x30, .g = 0x30, .b = 0x30, .a = 0xFF };
pub const C_TEXT      = rl.Color{ .r = 0xD2, .g = 0xD2, .b = 0xD2, .a = 0xFF };
pub const C_WHITE     = rl.Color{ .r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xFF };
pub const C_MUTED     = rl.Color{ .r = 0x9B, .g = 0x9B, .b = 0x9B, .a = 0xFF };
pub const C_ACCENT    = rl.Color{ .r = 0x5D, .g = 0xC2, .b = 0xAF, .a = 0xFF };
pub const C_CB_BORDER = rl.Color{ .r = 0xD9, .g = 0xD9, .b = 0xD9, .a = 0xFF };

pub const WIN_W: i32 = 800;
pub const WIN_H: i32 = 600;

pub const PAD_X: f32 = 24;
pub const PAD_Y: f32 = 10;

pub const TITLE_FONT_SIZE: i32 = 18;
pub const NORMAL_FONT_SIZE: i32 = 14;

pub const INPUT_H: f32    = 35;
pub const ITEM_H: f32     = 35;
pub const TAB_H: f32      = 28;
pub const CB_SIZE: f32    = 16;
pub const CB_MARGIN_RIGHT: f32 = 18;
pub const ITEM_RADIUS: f32 = 4;
pub const INPUT_RADIUS: f32 = 4;
pub const MARGIN_TITLE: f32 = 14;
pub const MARGIN_INPUT: f32 = 14;
pub const MARGIN_TAB: f32  = 3;
pub const MARGIN_ITEM: f32 = 5;