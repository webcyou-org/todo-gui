mod state;
mod style;
mod view;

use iced::executor;
use iced::{Application, Command, Element, Settings, Theme};

use state::{Message, TodoApp};

pub fn main() -> iced::Result {
    TodoApp::run(Settings::default())
}

impl Application for TodoApp {
    type Executor = executor::Default;
    type Message = Message;
    type Theme = Theme;
    type Flags = ();

    fn new(_flags: ()) -> (Self, Command<Message>) {
        (TodoApp::new(), Command::none())
    }

    fn title(&self) -> String {
        "ToDo".into()
    }

    fn update(&mut self, message: Message) -> Command<Message> {
        match message {
            Message::InputChanged(s) => self.input = s,
            Message::AddTodo => {
                let task = self.input.clone();
                self.add_todo(task);
                self.input = String::new();
            }
            Message::ToggleTodo(id) => self.toggle_todo(id),
            Message::SetTab(tab) => self.active_tab = tab,
        }
        Command::none()
    }

    fn view(&self) -> Element<'_, Message> {
        view::view(self)
    }
}