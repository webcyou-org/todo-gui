use crate::FUISystemError;

use super::qt_wrapper::{QClipboard, QString};

pub enum ClipboardMode {
    Clipboard,
    Selection,
    FindBuffer,
}

pub struct Clipboard {
    pub(crate) qclipboard: QClipboard,
}

impl Clipboard {
    pub fn set_text(&self, text: &str, mode: ClipboardMode) -> Result<(), FUISystemError> {
        let qtext = QString::from_str(&text)?;
        let mode = convert_mode(mode);
        self.qclipboard.set_text(&qtext, mode);
        Ok(())
    }

    pub fn get_text(&self, mode: ClipboardMode) -> Option<String> {
        let mode = convert_mode(mode);
        let qstring = self.qclipboard.text(mode);
        let result = qstring.as_string().unwrap_or_default();
        if result.is_empty() {
            None
        } else {
            Some(result)
        }
    }
}

fn convert_mode(mode: ClipboardMode) -> i32 {
    let mode = match mode {
        ClipboardMode::Clipboard => 0,
        ClipboardMode::Selection => 1,
        ClipboardMode::FindBuffer => 2,
    };
    mode
}
