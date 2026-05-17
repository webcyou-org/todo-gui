use fui_core::{Callback, Children, ControlObject, Horizontal, Property, ViewContext};
use fui_controls::{Button, Text};
use fui_macros::ui;
use std::cell::RefCell;
use std::rc::Rc;
use typemap::TypeMap;

pub fn build_tabs(
    on_all: Callback<()>,
    on_active: Callback<()>,
    on_completed: Callback<()>,
) -> Rc<RefCell<dyn ControlObject>> {
    ui!(
        Horizontal {
            Button {
                clicked: on_all,
                Text { text: Property::new("All".to_string()) }
            },
            Button {
                clicked: on_active,
                Text { text: Property::new("Active".to_string()) }
            },
            Button {
                clicked: on_completed,
                Text { text: Property::new("Completed".to_string()) }
            }
        }
    )
}