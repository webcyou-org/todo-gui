mod data;
mod theme;

use data::{default_todos, TabFilter, Todo};
use theme::*;

use fltk::{app, button, draw, enums, frame, group, input, prelude::*, window};
use std::cell::Cell;
use std::rc::Rc;

enum Message {
    AddTodo(String),
    SetTab(TabFilter),
    ToggleTodo(u32),
}

fn main() {
    let app = app::App::default();
    let (s, r) = app::channel::<Message>();

    let mut todos = default_todos();
    let mut active_tab = TabFilter::All;
    let mut next_id = 5u32;

    // Window
    let mut wind = window::Window::default()
        .with_size(800, 600)
        .with_label("ToDo");
    wind.set_color(C_BG);

    let x = 24;
    let mut y = 10;
    let w = 752;

    // Title
    let mut title = frame::Frame::new(x, y, w, 25, "ToDo");
    title.set_label_color(C_WHITE);
    title.set_label_size(18);
    title.set_label_font(enums::Font::HelveticaBold);
    title.set_align(enums::Align::Left | enums::Align::Inside);
    title.set_frame(enums::FrameType::NoBox);
    y += 25 + 14;

    // Input border (visible on focus)
    let mut input_border = frame::Frame::new(x - 1, y - 1, w + 2, 37, "");
    input_border.set_frame(enums::FrameType::FlatBox);
    input_border.set_color(C_BG);

    // Input field
    let mut input_field = input::Input::new(x, y, w, 35, "");
    input_field.set_color(C_INPUT);
    input_field.set_text_color(C_MUTED);
    input_field.set_text_size(14);
    input_field.set_frame(enums::FrameType::FlatBox);
    input_field.set_cursor_color(C_WHITE);
    input_field.set_value("Add Task");
    y += 35 + 14;

    let is_placeholder = Rc::new(Cell::new(true));

    {
        let s = s.clone();
        let ph = is_placeholder.clone();
        let mut border = input_border.clone();
        input_field.handle(move |inp, ev| match ev {
            enums::Event::Focus => {
                if ph.get() {
                    inp.set_value("");
                    inp.set_text_color(C_WHITE);
                    ph.set(false);
                }
                border.set_color(C_ACCENT);
                border.redraw();
                false
            }
            enums::Event::Unfocus => {
                if inp.value().trim().is_empty() {
                    inp.set_value("Add Task");
                    inp.set_text_color(C_MUTED);
                    ph.set(true);
                }
                border.set_color(C_BG);
                border.redraw();
                false
            }
            enums::Event::KeyDown => {
                if app::event_key() == enums::Key::Enter {
                    let text = inp.value().trim().to_string();
                    if !text.is_empty() && !ph.get() {
                        s.send(Message::AddTodo(text));
                        inp.set_value("");
                    }
                    true
                } else {
                    false
                }
            }
            _ => false,
        });
    }

    // Tab buttons
    let mut tab_all = button::Button::new(x, y, 40, 28, "All");
    let mut tab_active = button::Button::new(x + 40, y, 60, 28, "Active");
    let mut tab_completed = button::Button::new(x + 100, y, 95, 28, "Completed");

    for tab in [&mut tab_all, &mut tab_active, &mut tab_completed] {
        tab.set_color(C_BG);
        tab.set_label_color(C_TEXT);
        tab.set_label_size(14);
        tab.set_frame(enums::FrameType::FlatBox);
        tab.clear_visible_focus();
    }
    tab_all.set_label_font(enums::Font::HelveticaBold);

    {
        let s = s.clone();
        tab_all.set_callback(move |_| s.send(Message::SetTab(TabFilter::All)));
    }
    {
        let s = s.clone();
        tab_active.set_callback(move |_| s.send(Message::SetTab(TabFilter::Active)));
    }
    {
        let s = s.clone();
        tab_completed.set_callback(move |_| s.send(Message::SetTab(TabFilter::Completed)));
    }
    y += 28 + 3;

    // Scroll area
    let scroll_h = 600 - y - 10;
    let mut scroll = group::Scroll::new(x, y, w, scroll_h, None);
    scroll.set_color(C_BG);
    scroll.set_frame(enums::FrameType::FlatBox);
    scroll.set_type(group::ScrollType::Vertical);

    let mut pack = group::Pack::new(x, y, w, 0, None);
    pack.set_spacing(5);
    pack.end();

    scroll.end();
    wind.end();
    wind.show();

    build_todo_list(&mut pack, &todos, active_tab, &s, w);

    while app.wait() {
        if let Some(msg) = r.recv() {
            match msg {
                Message::AddTodo(text) => {
                    let task = text.trim().to_string();
                    if !task.is_empty() {
                        todos.push(Todo {
                            id: next_id,
                            task,
                            is_completed: false,
                        });
                        next_id += 1;
                        build_todo_list(&mut pack, &todos, active_tab, &s, w);
                    }
                }
                Message::SetTab(tab) => {
                    active_tab = tab;
                    update_tab_styles(&mut tab_all, &mut tab_active, &mut tab_completed, tab);
                    build_todo_list(&mut pack, &todos, active_tab, &s, w);
                }
                Message::ToggleTodo(id) => {
                    if let Some(todo) = todos.iter_mut().find(|t| t.id == id) {
                        todo.is_completed = !todo.is_completed;
                    }
                    build_todo_list(&mut pack, &todos, active_tab, &s, w);
                }
            }
        }
    }
}

fn build_todo_list(
    pack: &mut group::Pack,
    todos: &[Todo],
    active_tab: TabFilter,
    sender: &app::Sender<Message>,
    pack_w: i32,
) {
    pack.clear();
    pack.begin();

    let filtered: Vec<&Todo> = todos.iter().filter(|t| active_tab.matches(t)).collect();

    for todo in &filtered {
        let item_h = 35;

        let mut row = group::Flex::default().with_size(pack_w, item_h);
        row.set_type(group::FlexType::Row);
        row.set_color(C_SURFACE);
        row.set_frame(enums::FrameType::RFlatBox);

        // Left padding
        let pad_left = frame::Frame::default();
        row.fixed(&pad_left, 10);

        // Checkbox
        let mut cb = button::Button::default();
        row.fixed(&cb, 16);
        cb.set_frame(enums::FrameType::NoBox);
        cb.clear_visible_focus();
        let is_completed = todo.is_completed;
        cb.draw(move |b| {
            draw_checkbox(b.x(), b.y(), b.width(), b.height(), is_completed);
        });
        let id = todo.id;
        let s = sender.clone();
        cb.set_callback(move |_| {
            s.send(Message::ToggleTodo(id));
        });

        // Spacing
        let spacer = frame::Frame::default();
        row.fixed(&spacer, 18);

        // Task text
        let mut label = frame::Frame::default();
        label.set_frame(enums::FrameType::NoBox);
        let task_text = todo.task.clone();
        label.draw(move |f| {
            draw_task_text(f.x(), f.y(), f.height(), &task_text, is_completed);
        });

        // Right padding
        let pad_right = frame::Frame::default();
        row.fixed(&pad_right, 10);

        row.end();
    }

    pack.end();

    let item_count = filtered.len();
    let total_h = if item_count > 0 {
        item_count as i32 * 35 + (item_count as i32 - 1) * 5
    } else {
        1
    };
    pack.set_size(pack.width(), total_h);

    if let Some(mut parent) = pack.parent() {
        parent.redraw();
    }
    pack.redraw();
}

fn draw_checkbox(x: i32, y: i32, w: i32, h: i32, checked: bool) {
    let size = 16;
    let cx = x + (w - size) / 2;
    let cy = y + (h - size) / 2;
    let mx = cx + size / 2;
    let my = cy + size / 2;

    // Clear background
    draw::set_draw_color(C_SURFACE);
    draw::draw_rectf(x, y, w, h);

    if checked {
        draw::set_draw_color(C_ACCENT);
        draw::draw_pie(cx, cy, size, size, 0.0, 360.0);
        // Checkmark
        draw::set_draw_color(C_WHITE);
        draw::set_line_style(draw::LineStyle::Solid, 2);
        draw::draw_line(mx - 4, my, mx - 1, my + 3);
        draw::draw_line(mx - 1, my + 3, mx + 4, my - 3);
        draw::set_line_style(draw::LineStyle::Solid, 0);
    } else {
        draw::set_draw_color(C_CB_BORDER);
        draw::set_line_style(draw::LineStyle::Solid, 2);
        draw::draw_arc(cx, cy, size, size, 0.0, 360.0);
        draw::set_line_style(draw::LineStyle::Solid, 0);
    }
}

fn draw_task_text(x: i32, y: i32, h: i32, text: &str, completed: bool) {
    let color = if completed { C_MUTED } else { C_TEXT };
    draw::set_draw_color(color);
    draw::set_font(enums::Font::Helvetica, 14);
    let text_y = y + h / 2 + 5;
    draw::draw_text(text, x, text_y);
    if completed {
        let text_width = draw::width(text) as i32;
        let line_y = text_y - 5;
        draw::set_line_style(draw::LineStyle::Solid, 1);
        draw::draw_line(x, line_y, x + text_width, line_y);
        draw::set_line_style(draw::LineStyle::Solid, 0);
    }
}

fn update_tab_styles(
    tab_all: &mut button::Button,
    tab_active: &mut button::Button,
    tab_completed: &mut button::Button,
    active: TabFilter,
) {
    tab_all.set_label_font(enums::Font::Helvetica);
    tab_active.set_label_font(enums::Font::Helvetica);
    tab_completed.set_label_font(enums::Font::Helvetica);

    match active {
        TabFilter::All => tab_all.set_label_font(enums::Font::HelveticaBold),
        TabFilter::Active => tab_active.set_label_font(enums::Font::HelveticaBold),
        TabFilter::Completed => tab_completed.set_label_font(enums::Font::HelveticaBold),
    }

    tab_all.redraw();
    tab_active.redraw();
    tab_completed.redraw();
}
