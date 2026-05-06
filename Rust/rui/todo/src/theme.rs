use vger::color::Color;

fn srgb_to_linear(s: f32) -> f32 {
    if s <= 0.04045 {
        s / 12.92
    } else {
        ((s + 0.055) / 1.055).powf(2.4)
    }
}

fn hex_linear(hex: &str) -> Color {
    let c = Color::hex(hex).unwrap();
    Color::new(
        srgb_to_linear(c.r),
        srgb_to_linear(c.g),
        srgb_to_linear(c.b),
        c.a,
    )
}

pub fn c_bg() -> Color { hex_linear("#1C1C1C") }
pub fn c_surface() -> Color { hex_linear("#2A2A2A") }
pub fn c_input() -> Color { hex_linear("#303030") }
pub fn c_text() -> Color { hex_linear("#D2D2D2") }
pub fn c_white() -> Color { hex_linear("#FFFFFF") }
pub fn c_muted() -> Color { hex_linear("#9B9B9B") }
pub fn c_accent() -> Color { hex_linear("#5DC2AF") }
pub fn c_cb_border() -> Color { hex_linear("#D9D9D9") }
