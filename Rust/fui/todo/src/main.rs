mod components;
mod data;

use anyhow::Result;
use components::{input::build_input, tabs::build_tabs, todo_item::make_todo_control};
use data::TabFilter;
use fui_app::{Application, Window, WindowOptions};
use fui_core::{
    Callback, Children, ControlObject, ObservableVec, Property, ViewModel, ViewContext, Vertical,
};
use fui_controls::{ScrollViewer, Text};
use fui_macros::ui;
use std::cell::RefCell;
use std::rc::Rc;
use tokio::task::LocalSet;
use typemap::TypeMap;

// (id, task, is_completed)
type TodoEntry = (u32, String, Property<bool>);

struct MainViewModel {
    input_text: Property<String>,
    filter: Property<TabFilter>,
    todos: RefCell<Vec<TodoEntry>>,
    visible_controls: ObservableVec<Rc<RefCell<dyn ControlObject>>>,
    next_id: RefCell<u32>,
}

impl MainViewModel {
    fn new() -> Rc<Self> {
        let vm = Rc::new(Self {
            input_text: Property::new(String::new()),
            filter: Property::new(TabFilter::All),
            todos: RefCell::new(vec![
                (1, "Buy groceries".to_string(), Property::new(false)),
                (2, "Walk the dog".to_string(), Property::new(false)),
                (3, "Read a book".to_string(), Property::new(true)),
            ]),
            visible_controls: ObservableVec::new(),
            next_id: RefCell::new(4),
        });
        vm.rebuild();
        vm
    }

    fn rebuild(self: &Rc<Self>) {
        let filter = self.filter.get();
        self.visible_controls.clear();
        let entries: Vec<TodoEntry> = self
            .todos
            .borrow()
            .iter()
            .map(|(id, task, ic)| (*id, task.clone(), ic.clone()))
            .collect();
        for (id, task, is_completed) in entries {
            let show = match filter {
                TabFilter::All => true,
                TabFilter::Active => !is_completed.get(),
                TabFilter::Completed => is_completed.get(),
            };
            if show {
                let vm_clone = self.clone();
                let toggle_cb = Callback::new_sync(move |_: ()| {
                    let cur = vm_clone
                        .todos
                        .borrow()
                        .iter()
                        .find(|(tid, _, _)| *tid == id)
                        .map(|(_, _, ic)| ic.get())
                        .unwrap_or(false);
                    if let Some((_, _, ic)) = vm_clone
                        .todos
                        .borrow()
                        .iter()
                        .find(|(tid, _, _)| *tid == id)
                    {
                        ic.set(!cur);
                    }
                    vm_clone.rebuild();
                });
                let ctrl = make_todo_control(id, task, is_completed, toggle_cb);
                self.visible_controls.push(ctrl);
            }
        }
    }

    fn add_todo(self: &Rc<Self>) {
        let task = self.input_text.get();
        if task.trim().is_empty() {
            return;
        }
        let id = {
            let mut next = self.next_id.borrow_mut();
            let id = *next;
            *next += 1;
            id
        };
        self.todos
            .borrow_mut()
            .push((id, task, Property::new(false)));
        self.input_text.set(String::new());
        self.rebuild();
    }

    fn set_filter(self: &Rc<Self>, filter: TabFilter) {
        self.filter.set(filter);
        self.rebuild();
    }
}

impl ViewModel for MainViewModel {
    fn create_view(self: &Rc<Self>) -> Rc<RefCell<dyn ControlObject>> {
        let vm1 = self.clone();
        let add_cb = Callback::new_sync(move |_: ()| vm1.add_todo());

        let vm2 = self.clone();
        let all_cb = Callback::new_sync(move |_: ()| vm2.set_filter(TabFilter::All));

        let vm3 = self.clone();
        let active_cb = Callback::new_sync(move |_: ()| vm3.set_filter(TabFilter::Active));

        let vm4 = self.clone();
        let completed_cb =
            Callback::new_sync(move |_: ()| vm4.set_filter(TabFilter::Completed));

        let input_widget = build_input(self.input_text.clone(), add_cb);
        let tabs_widget = build_tabs(all_cb, active_cb, completed_cb);

        ui!(
            Vertical {
                Text { text: Property::new("ToDo".to_string()) },
                input_widget,
                tabs_widget,
                ScrollViewer {
                    Vertical {
                        &self.visible_controls,
                    }
                }
            }
        )
    }
}

#[tokio::main(flavor = "current_thread")]
async fn main() -> Result<()> {
    LocalSet::new()
        .run_until(async {
            let app = Application::new("Todo").await?;
            let mut window = Window::create(
                WindowOptions::new()
                    .with_title("ToDo")
                    .with_size(800, 600),
            )
            .await?;

            let vm = MainViewModel::new();
            window.set_vm(vm);

            app.run().await?;
            Ok(())
        })
        .await
}