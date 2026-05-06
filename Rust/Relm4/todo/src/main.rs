mod components;
mod data;
mod theme;

use components::todo_item::{TodoItemInit, TodoItemOutput};
use data::{default_todos, TabFilter, Todo};

use gtk::prelude::*;
use relm4::factory::FactoryVecDeque;
use relm4::prelude::*;

struct App {
    todos: Vec<Todo>,
    todos_factory: FactoryVecDeque<components::todo_item::TodoItem>,
    active_tab: TabFilter,
    next_id: u32,
}

#[derive(Debug)]
enum AppMsg {
    AddTodo(String),
    SetTab(TabFilter),
    ToggleTodo(u32),
}

#[relm4::component]
impl SimpleComponent for App {
    type Init = ();
    type Input = AppMsg;
    type Output = ();

    view! {
        gtk::Window {
            set_title: Some("ToDo"),
            set_default_size: (800, 600),

            gtk::Box {
                set_orientation: gtk::Orientation::Vertical,
                set_margin_top: 10,
                set_margin_bottom: 10,
                set_margin_start: 24,
                set_margin_end: 24,

                // Title
                gtk::Label {
                    set_label: "ToDo",
                    set_halign: gtk::Align::Start,
                    add_css_class: "title-label",
                    set_margin_bottom: 14,
                },

                // Input
                gtk::Entry {
                    set_placeholder_text: Some("Add Task"),
                    add_css_class: "todo-input",
                    set_hexpand: true,
                    set_margin_bottom: 14,
                    connect_activate[sender] => move |entry| {
                        let text = entry.text().to_string();
                        sender.input(AppMsg::AddTodo(text));
                        entry.set_text("");
                    },
                },

                // Tabs
                gtk::Box {
                    set_orientation: gtk::Orientation::Horizontal,
                    set_margin_bottom: 3,
                    set_halign: gtk::Align::Start,

                    gtk::Button {
                        set_label: "All",
                        #[watch]
                        set_css_classes: if model.active_tab == TabFilter::All {
                            &["tab-button", "tab-button-active"]
                        } else {
                            &["tab-button"]
                        },
                        connect_clicked => AppMsg::SetTab(TabFilter::All),
                    },

                    gtk::Button {
                        set_label: "Active",
                        #[watch]
                        set_css_classes: if model.active_tab == TabFilter::Active {
                            &["tab-button", "tab-button-active"]
                        } else {
                            &["tab-button"]
                        },
                        connect_clicked => AppMsg::SetTab(TabFilter::Active),
                    },

                    gtk::Button {
                        set_label: "Completed",
                        #[watch]
                        set_css_classes: if model.active_tab == TabFilter::Completed {
                            &["tab-button", "tab-button-active"]
                        } else {
                            &["tab-button"]
                        },
                        connect_clicked => AppMsg::SetTab(TabFilter::Completed),
                    },
                },

                // Todo list
                gtk::ScrolledWindow {
                    set_vexpand: true,
                    set_hscrollbar_policy: gtk::PolicyType::Never,

                    #[local_ref]
                    todo_list_box -> gtk::Box {
                        set_orientation: gtk::Orientation::Vertical,
                    }
                }
            }
        }
    }

    fn init(
        _init: Self::Init,
        root: Self::Root,
        sender: ComponentSender<Self>,
    ) -> ComponentParts<Self> {
        let default = default_todos();
        let next_id = default.len() as u32 + 1;

        let mut todos_factory = FactoryVecDeque::builder()
            .launch(gtk::Box::default())
            .forward(sender.input_sender(), |output| match output {
                TodoItemOutput::Toggle(id) => AppMsg::ToggleTodo(id),
            });

        {
            let mut guard = todos_factory.guard();
            for todo in &default {
                guard.push_back(TodoItemInit {
                    id: todo.id,
                    task: todo.task.clone(),
                    is_completed: todo.is_completed,
                });
            }
        }

        let model = App {
            todos: default,
            todos_factory,
            active_tab: TabFilter::All,
            next_id,
        };

        let todo_list_box = model.todos_factory.widget();
        let widgets = view_output!();

        ComponentParts { model, widgets }
    }

    fn update(&mut self, msg: Self::Input, _sender: ComponentSender<Self>) {
        match msg {
            AppMsg::AddTodo(text) => {
                let task = text.trim().to_string();
                if task.is_empty() {
                    return;
                }
                self.todos.push(Todo {
                    id: self.next_id,
                    task,
                    is_completed: false,
                });
                self.next_id += 1;
                self.rebuild_list();
            }
            AppMsg::SetTab(tab) => {
                self.active_tab = tab;
                self.rebuild_list();
            }
            AppMsg::ToggleTodo(id) => {
                if let Some(todo) = self.todos.iter_mut().find(|t| t.id == id) {
                    todo.is_completed = !todo.is_completed;
                }
                self.rebuild_list();
            }
        }
    }
}

impl App {
    fn rebuild_list(&mut self) {
        let mut guard = self.todos_factory.guard();
        guard.clear();
        for todo in &self.todos {
            if self.active_tab.matches(todo) {
                guard.push_back(TodoItemInit {
                    id: todo.id,
                    task: todo.task.clone(),
                    is_completed: todo.is_completed,
                });
            }
        }
    }
}

fn main() {
    let app = RelmApp::new("com.github.webcyou-org.todo-gui.relm4.todo");
    relm4::set_global_css(theme::APP_CSS);
    app.run::<App>(());
}
