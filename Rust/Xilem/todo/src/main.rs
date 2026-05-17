mod components;
mod data;
mod theme;

use components::input::todo_input;
use components::tabs::tab_menu;
use components::todo_item::todo_list;
use data::AppState;
use theme::C_BG;
use tracing_subscriber::filter::LevelFilter;
use xilem::masonry::properties::Padding;
use xilem::masonry::properties::types::AsUnit as _;
use xilem::style::Style as _;
use xilem::view::{CrossAxisAlignment, FlexExt as _, FlexSpacer, flex_col, label};
use xilem::winit::dpi::LogicalSize;
use xilem::winit::error::EventLoopError;
use xilem::{Color, EventLoop, FontWeight, WidgetView, WindowOptions, Xilem};

fn app_logic(state: &mut AppState) -> impl WidgetView<AppState> + use<> {
    let title = label("ToDo")
        .text_size(18.)
        .weight(FontWeight::BOLD)
        .color(Color::from_rgb8(0xFF, 0xFF, 0xFF));

    let input = todo_input(state);
    let tabs = tab_menu(state.active_tab);
    let list = todo_list(state.filtered_todos()).flex(1.);

    flex_col((
        title,
        FlexSpacer::Fixed(14.px()),
        input,
        FlexSpacer::Fixed(14.px()),
        tabs,
        FlexSpacer::Fixed(1.px()),
        list,
    ))
    .cross_axis_alignment(CrossAxisAlignment::Fill)
    .background_color(C_BG)
    .padding(Padding::from_vh(10., 24.))
}

fn main() -> Result<(), EventLoopError> {
    // Register WARN-level subscriber before Masonry sets its default DEBUG subscriber.
    // Masonry respects an already-set subscriber, so this suppresses debug/info noise.
    let _ = tracing_subscriber::fmt()
        .with_max_level(LevelFilter::WARN)
        .try_init();

    let data = AppState::new();
    let app = Xilem::new_simple(
        data,
        app_logic,
        WindowOptions::new("ToDo")
            .with_initial_inner_size(LogicalSize::new(800.0_f64, 600.0_f64)),
    );
    app.run_in(EventLoop::with_user_event())
}