use azul::prelude::*;
use azul::css::ColorU;
use azul::option::OptionColorU;

mod data;
mod theme;
mod components;

use data::AppState;
use components::input::build_input;
use components::tabs::build_tabs;
use components::todo_list::build_todo_list;

extern "C" fn layout(mut data: RefAny, _: LayoutCallbackInfo) -> Dom {
    let state = match data.downcast_ref::<AppState>() {
        Some(s) => (*s).clone(),
        None => return Dom::create_body(),
    };

    let title = Dom::create_text("ToDo")
        .with_inline_style(
            "color: rgb(255,255,255); font-size: 18px; font-weight: bold; margin-bottom: 14px;"
        );

    let content = Dom::create_div()
        .with_inline_style(
            "background-color: rgb(28,28,28); \
             padding-top: 10px; padding-bottom: 10px; \
             padding-left: 24px; padding-right: 24px; \
             flex-direction: column; flex-grow: 1; \
             width: 100%; height: 100%;"
        )
        .with_child(title)
        .with_child(build_input(&state, data.clone()))
        .with_child(build_tabs(&state, data.clone()))
        .with_child(build_todo_list(&state, data.clone()));

    Dom::create_body()
        .with_inline_style(
            "background-color: rgb(28,28,28); \
             margin: 0; padding: 0; \
             flex-direction: column; width: 100%; height: 100%;"
        )
        .with_child(content)
}

fn main() {
    let app = App::create(RefAny::new(AppState::new()), AppConfig::create());
    let mut window = WindowCreateOptions::create(layout);
    window.window_state.title = "ToDo".into();
    window.window_state.size.dimensions = LogicalSize { width: 800.0, height: 600.0 };
    window.window_state.background_color = OptionColorU::Some(ColorU { r: 28, g: 28, b: 28, a: 255 });
    app.run(window);
}