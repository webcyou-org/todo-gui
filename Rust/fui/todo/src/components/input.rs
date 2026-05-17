use fui_core::{Callback, Children, ControlObject, Horizontal, Property, ViewContext};
use fui_controls::{Button, Text, TextBox};
use fui_macros::ui;
use std::cell::RefCell;
use std::rc::Rc;
use typemap::TypeMap;

pub fn build_input(
    text: Property<String>,
    on_add: Callback<()>,
) -> Rc<RefCell<dyn ControlObject>> {
    ui!(
        Horizontal {
            TextBox { text: text },
            Button {
                clicked: on_add,
                Text { text: Property::new("Add".to_string()) }
            }
        }
    )
}