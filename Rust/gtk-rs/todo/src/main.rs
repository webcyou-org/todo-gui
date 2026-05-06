mod data;
mod theme;

use data::{default_todos, TabFilter, Todo};
use theme::APP_CSS;

use gtk::prelude::*;
use gtk::{self, gdk, gio};
use std::cell::RefCell;
use std::rc::Rc;

struct AppState {
    todos: Vec<Todo>,
    active_tab: TabFilter,
    next_id: u32,
}

fn main() {
    let application = gtk::Application::new(
        Some("com.github.webcyou-org.todo-gui.gtk-rs.todo"),
        gio::ApplicationFlags::default(),
    );
    application.connect_activate(build_ui);
    application.run();
}

fn build_ui(application: &gtk::Application) {
    // CSS
    let provider = gtk::CssProvider::new();
    provider.load_from_data(APP_CSS);
    gtk::style_context_add_provider_for_display(
        &gdk::Display::default().expect("display"),
        &provider,
        gtk::STYLE_PROVIDER_PRIORITY_APPLICATION,
    );

    // State
    let state = Rc::new(RefCell::new(AppState {
        todos: default_todos(),
        active_tab: TabFilter::All,
        next_id: 5,
    }));

    // Window
    let window = gtk::ApplicationWindow::new(application);
    window.set_title(Some("ToDo"));
    window.set_default_size(800, 600);

    // Main container
    let main_box = gtk::Box::new(gtk::Orientation::Vertical, 0);
    main_box.set_margin_top(10);
    main_box.set_margin_bottom(10);
    main_box.set_margin_start(24);
    main_box.set_margin_end(24);

    // Title
    let title = gtk::Label::new(Some("ToDo"));
    title.add_css_class("title-label");
    title.set_halign(gtk::Align::Start);
    title.set_margin_bottom(14);
    main_box.append(&title);

    // Input
    let entry = gtk::Entry::new();
    entry.set_placeholder_text(Some("Add Task"));
    entry.add_css_class("todo-input");
    entry.set_hexpand(true);
    entry.set_margin_bottom(14);
    main_box.append(&entry);

    // Tab bar
    let tab_box = gtk::Box::new(gtk::Orientation::Horizontal, 0);
    tab_box.set_margin_bottom(3);

    let tab_all = gtk::Button::with_label("All");
    let tab_active = gtk::Button::with_label("Active");
    let tab_completed = gtk::Button::with_label("Completed");

    for tab in [&tab_all, &tab_active, &tab_completed] {
        tab.add_css_class("tab-button");
        tab_box.append(tab);
    }
    tab_all.add_css_class("tab-button-active");
    main_box.append(&tab_box);

    // Scrolled list
    let scrolled = gtk::ScrolledWindow::new();
    scrolled.set_vexpand(true);
    scrolled.set_hscrollbar_policy(gtk::PolicyType::Never);

    let list_box = gtk::Box::new(gtk::Orientation::Vertical, 5);
    scrolled.set_child(Some(&list_box));
    main_box.append(&scrolled);

    window.set_child(Some(&main_box));

    // Build initial list
    rebuild_list(&list_box, &state);

    // Entry activate (Enter key)
    {
        let state = state.clone();
        let list_box = list_box.clone();
        entry.connect_activate(move |e| {
            let text = e.text().trim().to_string();
            if !text.is_empty() {
                let mut s = state.borrow_mut();
                let id = s.next_id;
                s.next_id += 1;
                s.todos.push(Todo {
                    id,
                    task: text,
                    is_completed: false,
                });
                drop(s);
                e.set_text("");
                rebuild_list(&list_box, &state);
            }
        });
    }

    // Tab callbacks
    {
        let state = state.clone();
        let list_box = list_box.clone();
        let ta = tab_active.clone();
        let tc = tab_completed.clone();
        tab_all.connect_clicked(move |btn| {
            state.borrow_mut().active_tab = TabFilter::All;
            update_tab_classes(btn, &ta, &tc, TabFilter::All);
            rebuild_list(&list_box, &state);
        });
    }
    {
        let state = state.clone();
        let list_box = list_box.clone();
        let ta = tab_all.clone();
        let tc = tab_completed.clone();
        tab_active.connect_clicked(move |btn| {
            state.borrow_mut().active_tab = TabFilter::Active;
            update_tab_classes(&ta, btn, &tc, TabFilter::Active);
            rebuild_list(&list_box, &state);
        });
    }
    {
        let state = state.clone();
        let list_box = list_box.clone();
        let ta = tab_all.clone();
        let tb = tab_active.clone();
        tab_completed.connect_clicked(move |btn| {
            state.borrow_mut().active_tab = TabFilter::Completed;
            update_tab_classes(&ta, &tb, btn, TabFilter::Completed);
            rebuild_list(&list_box, &state);
        });
    }

    window.present();
}

fn rebuild_list(list_box: &gtk::Box, state: &Rc<RefCell<AppState>>) {
    // Remove all children
    while let Some(child) = list_box.first_child() {
        list_box.remove(&child);
    }

    let s = state.borrow();
    let filtered: Vec<&Todo> = s.todos.iter().filter(|t| s.active_tab.matches(t)).collect();

    for todo in &filtered {
        let row = gtk::Box::new(gtk::Orientation::Horizontal, 0);
        row.add_css_class("todo-item-box");

        // Checkbox
        let check = gtk::CheckButton::new();
        check.set_active(todo.is_completed);
        check.add_css_class("todo-checkbox");
        row.append(&check);

        // Label
        let label = gtk::Label::new(Some(&todo.task));
        label.add_css_class("todo-text");
        if todo.is_completed {
            label.add_css_class("todo-text-completed");
        }
        label.set_hexpand(true);
        label.set_halign(gtk::Align::Start);
        row.append(&label);

        let id = todo.id;
        let state_clone = state.clone();
        let list_box_clone = list_box.clone();
        check.connect_toggled(move |_| {
            {
                let mut s = state_clone.borrow_mut();
                if let Some(t) = s.todos.iter_mut().find(|t| t.id == id) {
                    t.is_completed = !t.is_completed;
                }
            }
            rebuild_list(&list_box_clone, &state_clone);
        });

        list_box.append(&row);
    }
}

fn update_tab_classes(
    tab_all: &gtk::Button,
    tab_active: &gtk::Button,
    tab_completed: &gtk::Button,
    active: TabFilter,
) {
    tab_all.remove_css_class("tab-button-active");
    tab_active.remove_css_class("tab-button-active");
    tab_completed.remove_css_class("tab-button-active");

    match active {
        TabFilter::All => tab_all.add_css_class("tab-button-active"),
        TabFilter::Active => tab_active.add_css_class("tab-button-active"),
        TabFilter::Completed => tab_completed.add_css_class("tab-button-active"),
    }
}
