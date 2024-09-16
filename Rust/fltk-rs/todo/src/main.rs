use fltk::{app, prelude::*, window::Window};

fn main() {
    let app = app::App::default();
    let mut wind = Window::new(100, 100, 400, 300, "ToDo Application");
    wind.end();
    wind.show();
    app.run().unwrap();
}