use iced::widget::{button, container, text_input};
use iced::{Background, Border, Color, Shadow, Theme, Vector};

// ─── Color palette ────────────────────────────────────────────────────────────
pub const C_BG:      Color = Color { r: 0.110, g: 0.110, b: 0.110, a: 1.0 }; // #1C1C1C
pub const C_SURFACE: Color = Color { r: 0.165, g: 0.165, b: 0.165, a: 1.0 }; // #2A2A2A
pub const C_INPUT:   Color = Color { r: 0.188, g: 0.188, b: 0.188, a: 1.0 }; // #303030
pub const C_TEXT:    Color = Color { r: 0.824, g: 0.824, b: 0.824, a: 1.0 }; // #D2D2D2
pub const C_MUTED:   Color = Color { r: 0.608, g: 0.608, b: 0.608, a: 1.0 }; // #9B9B9B
pub const C_ACCENT:  Color = Color { r: 0.365, g: 0.761, b: 0.686, a: 1.0 }; // #5DC2AF
pub const C_HOVER:   Color = Color { r: 0.200, g: 0.200, b: 0.200, a: 1.0 };

// ─── Container ────────────────────────────────────────────────────────────────
pub fn bg_container(_: &Theme) -> container::Appearance {
    container::Appearance {
        background: Some(Background::Color(C_BG)),
        ..Default::default()
    }
}

// ─── Text input ───────────────────────────────────────────────────────────────
pub struct InputStyle;

impl text_input::StyleSheet for InputStyle {
    type Style = Theme;

    fn active(&self, _: &Theme) -> text_input::Appearance {
        text_input::Appearance {
            background: Background::Color(C_INPUT),
            border: Border { width: 0.0, color: Color::TRANSPARENT, radius: 4.0.into() },
            icon_color: C_MUTED,
        }
    }

    fn focused(&self, _: &Theme) -> text_input::Appearance {
        text_input::Appearance {
            background: Background::Color(C_INPUT),
            border: Border { width: 1.0, color: C_ACCENT, radius: 4.0.into() },
            icon_color: C_MUTED,
        }
    }

    fn hovered(&self, theme: &Theme) -> text_input::Appearance {
        self.focused(theme)
    }

    fn disabled(&self, _: &Theme) -> text_input::Appearance {
        text_input::Appearance {
            background: Background::Color(C_INPUT),
            border: Border { width: 0.0, color: Color::TRANSPARENT, radius: 4.0.into() },
            icon_color: C_MUTED,
        }
    }

    fn placeholder_color(&self, _: &Theme) -> Color { C_MUTED }
    fn value_color(&self, _: &Theme) -> Color { Color::WHITE }
    fn disabled_color(&self, _: &Theme) -> Color { C_MUTED }
    fn selection_color(&self, _: &Theme) -> Color { C_ACCENT }
}

// ─── Tab button ───────────────────────────────────────────────────────────────
pub struct TabButtonStyle {
    pub active: bool,
}

impl button::StyleSheet for TabButtonStyle {
    type Style = Theme;

    fn active(&self, _: &Theme) -> button::Appearance {
        button::Appearance {
            background: None,
            text_color: if self.active { C_ACCENT } else { C_TEXT },
            border: Border::default(),
            shadow: Shadow::default(),
            shadow_offset: Vector::default(),
        }
    }

    fn hovered(&self, theme: &Theme) -> button::Appearance {
        button::Appearance { text_color: C_ACCENT, ..self.active(theme) }
    }

    fn pressed(&self, theme: &Theme) -> button::Appearance {
        self.hovered(theme)
    }
}

// ─── Todo row button ──────────────────────────────────────────────────────────
pub struct TodoRowStyle;

impl button::StyleSheet for TodoRowStyle {
    type Style = Theme;

    fn active(&self, _: &Theme) -> button::Appearance {
        button::Appearance {
            background: Some(Background::Color(C_SURFACE)),
            text_color: C_TEXT,
            border: Border { radius: 4.0.into(), width: 0.0, color: Color::TRANSPARENT },
            shadow: Shadow::default(),
            shadow_offset: Vector::default(),
        }
    }

    fn hovered(&self, theme: &Theme) -> button::Appearance {
        button::Appearance { background: Some(Background::Color(C_HOVER)), ..self.active(theme) }
    }

    fn pressed(&self, theme: &Theme) -> button::Appearance {
        self.hovered(theme)
    }
}