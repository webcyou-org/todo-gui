use super::QString;

pub struct QClipboard {
    pub this: *mut ::std::os::raw::c_void,
}

impl QClipboard {
    pub fn set_text(&self, text: &QString, mode: i32) {
        unsafe {
            crate::platform::qt::qt_wrapper::QClipboard_setText(self.this, text.this, mode);
        }
    }

    pub fn text(&self, mode: i32) -> QString {
        unsafe {
            let qstring_ptr = crate::platform::qt::qt_wrapper::QClipboard_text(self.this, mode);
            QString {
                this: qstring_ptr,
                is_owned: true,
            }
        }
    }
}
