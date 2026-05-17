///
/// Global application options.
///
pub struct ApplicationOptions {
    pub title: String,

    pub opengl_share_contexts: bool,
    pub opengl_stencil_bits: i32,
    pub opengl_depth_bits: i32,

    pub force_xwayland: bool,
}

impl Default for ApplicationOptions {
    fn default() -> Self {
        Self::new()
    }
}

impl ApplicationOptions {
    ///
    /// Creates new builder.
    ///
    pub fn new() -> Self {
        Self {
            title: "".to_string(),
            opengl_share_contexts: false,
            opengl_stencil_bits: 0,
            opengl_depth_bits: 0,
            force_xwayland: false,
        }
    }

    ///
    /// Sets the application title.
    ///
    pub fn with_title(mut self, title: &str) -> Self {
        self.title = title.to_string();
        self
    }

    ///
    /// Enables automatically created shared contexts between windows.
    ///
    pub fn with_opengl_share_contexts(mut self, share: bool) -> Self {
        self.opengl_share_contexts = share;
        self
    }

    ///
    /// Sets bits of the the stencil buffer.
    /// 0 - disables stencil buffer, 8 - standard stencil buffer.
    ///
    pub fn with_opengl_stencil_bits(mut self, bits: i32) -> Self {
        self.opengl_stencil_bits = bits;
        self
    }

    ///
    /// Sets bits of the the depth buffer.
    /// 0 - disables depth buffer, 24 - standard depth buffer.
    ///
    pub fn with_opengl_depth_bits(mut self, bits: i32) -> Self {
        self.opengl_depth_bits = bits;
        self
    }

    ///
    /// Forces the window to be opened on XWayland (xcb) under Wayland.
    ///
    pub fn with_force_xwayland(mut self, force: bool) -> Self {
        self.force_xwayland = force;
        self
    }
}
