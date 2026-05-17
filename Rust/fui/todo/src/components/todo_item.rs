use fui_core::{Callback, ControlObject, Property};
use fui_controls::{Button, Text};
use fui_macros::ui;
use std::cell::RefCell;
use std::rc::Rc;
use typemap::TypeMap;
use fui_core::{Children, ViewContext};

pub fn make_todo_control(
    id: u32,
    task: String,
    is_completed: Property<bool>,
    on_toggle: Callback<()>,
) -> Rc<RefCell<dyn ControlObject>> {
    let label = Property::binded_c_from(&is_completed, {
        let task = task.clone();
        move |done: bool| {
            if done {
                format!("[x] {}", task)
            } else {
                format!("[ ] {}", task)
            }
        }
    });

    ui!(
        Button {
            clicked: on_toggle,
            Text { text: label }
        }
    )
}