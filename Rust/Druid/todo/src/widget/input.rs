use druid::widget::{Controller, TextBox};
use druid::{Color, Env, Event, EventCtx, KbKey, Widget, WidgetExt, theme};

use crate::data::AppState;
use crate::theme::{ACCENT, INPUT_BG, TEXT_HINT, TEXT_WHITE};

struct InputController;

impl<W: Widget<AppState>> Controller<AppState, W> for InputController {
    fn event(
        &mut self,
        child: &mut W,
        ctx: &mut EventCtx,
        event: &Event,
        data: &mut AppState,
        env: &Env,
    ) {
        if let Event::KeyDown(key_event) = event {
            if key_event.key == KbKey::Enter {
                data.add_todo();
                ctx.set_handled();
                return;
            }
        }
        child.event(ctx, event, data, env);
    }
}

pub fn build_input() -> impl Widget<AppState> {
    TextBox::new()
        .with_placeholder("Add Task")
        .lens(AppState::input)
        .controller(InputController)
        .fix_height(35.0)
        .expand_width()
        .env_scope(|env, _: &AppState| {
            env.set(theme::BACKGROUND_LIGHT,      INPUT_BG);
            env.set(theme::BORDER_DARK,           Color::TRANSPARENT);
            env.set(theme::PRIMARY_LIGHT,         ACCENT);
            env.set(theme::TEXT_COLOR,            TEXT_WHITE);
            env.set(theme::PLACEHOLDER_COLOR,     TEXT_HINT);
            env.set(theme::TEXTBOX_BORDER_RADIUS, 4.0_f64);
        })
}