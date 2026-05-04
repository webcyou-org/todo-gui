use iced::widget::{button, column, container, row, scrollable, text, text_input};
use iced::{Color, Element, Font, Length, Padding};

use crate::state::{Message, Tab, TodoApp, TodoItem};
use crate::style::{
    bg_container, InputStyle, TabButtonStyle, TodoRowStyle,
    C_ACCENT, C_MUTED, C_TEXT,
};

pub fn view(app: &TodoApp) -> Element<'_, Message> {
    let title = text("ToDo")
        .size(18)
        .style(Color::WHITE)
        .font(Font { weight: iced::font::Weight::Bold, ..Font::default() });

    let input = text_input("Add Task", &app.input)
        .on_input(Message::InputChanged)
        .on_submit(Message::AddTodo)
        .size(14)
        .padding([8, 10])
        .style(iced::theme::TextInput::Custom(Box::new(InputStyle)));

    let input_row = container(input).height(35).width(Length::Fill);

    let tabs = row![
        make_tab("All", Tab::All, &app.active_tab),
        make_tab("Active", Tab::Active, &app.active_tab),
        make_tab("Completed", Tab::Completed, &app.active_tab),
    ]
    .height(28);

    let list_items: Vec<Element<Message>> =
        app.filtered_todos().iter().map(|item| make_todo_row(item)).collect();

    let list_col = column(list_items).spacing(5);
    let list = scrollable(list_col).height(Length::Fill);

    let content = column![title, input_row, tabs, list]
        .spacing(10)
        .padding(Padding { top: 10.0, right: 24.0, bottom: 10.0, left: 24.0 });

    container(content)
        .width(Length::Fill)
        .height(Length::Fill)
        .style(bg_container)
        .into()
}

fn make_tab<'a>(label: &'a str, tab: Tab, active_tab: &Tab) -> Element<'a, Message> {
    let is_active = &tab == active_tab;
    button(text(label).size(14).style(if is_active { C_ACCENT } else { C_TEXT }))
        .on_press(Message::SetTab(tab))
        .padding([4, 8])
        .style(iced::theme::Button::Custom(Box::new(TabButtonStyle { active: is_active })))
        .into()
}

fn make_todo_row(item: &TodoItem) -> Element<'_, Message> {
    let check = text(if item.completed { "✓" } else { "○" })
        .size(14)
        .style(if item.completed { C_ACCENT } else { C_MUTED });

    let label = text(item.task.as_str())
        .size(14)
        .style(if item.completed { C_MUTED } else { C_TEXT });

    let content = container(
        row![check, label]
            .spacing(8)
            .align_items(iced::Alignment::Center),
    )
    .center_y()
    .width(Length::Fill)
    .height(Length::Fill);

    let id = item.id;
    button(content)
        .on_press(Message::ToggleTodo(id))
        .width(Length::Fill)
        .padding([0, 10])
        .height(35)
        .style(iced::theme::Button::Custom(Box::new(TodoRowStyle)))
        .into()
}