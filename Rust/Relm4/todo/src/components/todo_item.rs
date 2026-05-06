use gtk::prelude::*;
use relm4::factory::{DynamicIndex, FactoryComponent, FactorySender};
use relm4::prelude::*;

#[derive(Debug)]
pub struct TodoItem {
    pub id: u32,
    pub task: String,
    pub is_completed: bool,
}

pub struct TodoItemInit {
    pub id: u32,
    pub task: String,
    pub is_completed: bool,
}

#[derive(Debug)]
pub enum TodoItemInput {
    Toggle,
}

#[derive(Debug)]
pub enum TodoItemOutput {
    Toggle(u32),
}

#[relm4::factory(pub)]
impl FactoryComponent for TodoItem {
    type Init = TodoItemInit;
    type Input = TodoItemInput;
    type Output = TodoItemOutput;
    type CommandOutput = ();
    type ParentWidget = gtk::Box;

    view! {
        #[root]
        gtk::Box {
            set_orientation: gtk::Orientation::Horizontal,
            set_hexpand: true,
            add_css_class: "todo-item-box",
            set_margin_bottom: 5,

            gtk::CheckButton {
                set_active: self.is_completed,
                add_css_class: "todo-checkbox",
                connect_toggled[sender] => move |_btn| {
                    sender.input(TodoItemInput::Toggle);
                },
            },

            gtk::Label {
                set_label: &self.task,
                set_css_classes: if self.is_completed {
                    &["todo-text", "todo-text-completed"]
                } else {
                    &["todo-text"]
                },
                set_halign: gtk::Align::Start,
                set_hexpand: true,
            },
        }
    }

    fn init_model(init: Self::Init, _index: &DynamicIndex, _sender: FactorySender<Self>) -> Self {
        TodoItem {
            id: init.id,
            task: init.task,
            is_completed: init.is_completed,
        }
    }

    fn update(&mut self, msg: Self::Input, sender: FactorySender<Self>) {
        match msg {
            TodoItemInput::Toggle => {
                let _ = sender.output(TodoItemOutput::Toggle(self.id));
            }
        }
    }
}
