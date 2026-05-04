use druid::kurbo::{BezPath, Circle, Line};
use druid::piet::RenderContext;
use druid::widget::{CrossAxisAlignment, Flex, Label, Painter};
use druid::{
    BoxConstraints, Env, Event, EventCtx, Insets, LayoutCtx, LifeCycle,
    LifeCycleCtx, PaintCtx, Size, UpdateCtx, Widget, WidgetExt,
};

use crate::data::Todo;
use crate::theme::{ACCENT, CHECKBOX_BORDER, ITEM_BG, TEXT_MAIN};

// ---------------------------------------------------------------------------
// Strikethrough<W> — 完了時に child の上へ横線を描画するラッパー
// ---------------------------------------------------------------------------

pub struct Strikethrough<W>(pub W);

impl<W: Widget<Todo>> Widget<Todo> for Strikethrough<W> {
    fn event(&mut self, ctx: &mut EventCtx, event: &Event, data: &mut Todo, env: &Env) {
        self.0.event(ctx, event, data, env);
    }
    fn lifecycle(&mut self, ctx: &mut LifeCycleCtx, event: &LifeCycle, data: &Todo, env: &Env) {
        self.0.lifecycle(ctx, event, data, env);
    }
    fn update(&mut self, ctx: &mut UpdateCtx, old_data: &Todo, data: &Todo, env: &Env) {
        self.0.update(ctx, old_data, data, env);
    }
    fn layout(&mut self, ctx: &mut LayoutCtx, bc: &BoxConstraints, data: &Todo, env: &Env) -> Size {
        self.0.layout(ctx, bc, data, env)
    }
    fn paint(&mut self, ctx: &mut PaintCtx, data: &Todo, env: &Env) {
        self.0.paint(ctx, data, env);
        if data.is_completed {
            let size = ctx.size();
            let mid_y = size.height / 2.0;
            ctx.stroke(Line::new((0.0, mid_y), (size.width, mid_y)), &TEXT_MAIN, 1.0);
        }
    }
}

// ---------------------------------------------------------------------------
// 円形チェックボックス
// ---------------------------------------------------------------------------

pub fn make_checkbox() -> impl Widget<Todo> {
    Painter::new(|ctx, todo: &Todo, _env| {
        let size = ctx.size();
        let (cx, cy) = (size.width / 2.0, size.height / 2.0);
        let circle = Circle::new((cx, cy), 7.0);

        if todo.is_completed {
            ctx.stroke(circle, &ACCENT, 2.0);
            let mut path = BezPath::new();
            path.move_to((cx - 3.5, cy + 0.5));
            path.line_to((cx - 0.5, cy + 3.0));
            path.line_to((cx + 4.0, cy - 2.5));
            ctx.stroke(path, &ACCENT, 1.5);
        } else {
            ctx.stroke(circle, &CHECKBOX_BORDER, 2.0);
        }
    })
    .fix_size(16.0, 16.0)
    .on_click(|_ctx, todo: &mut Todo, _env| {
        todo.is_completed = !todo.is_completed;
    })
}

// ---------------------------------------------------------------------------
// Todo 行
// ---------------------------------------------------------------------------

pub fn make_todo_row() -> impl Widget<Todo> {
    let row = Flex::row()
        .cross_axis_alignment(CrossAxisAlignment::Center)
        .with_child(make_checkbox())
        .with_spacer(18.0)
        .with_flex_child(
            Strikethrough(
                Label::dynamic(|todo: &Todo, _| todo.task.clone())
                    .with_text_color(TEXT_MAIN)
                    .with_text_size(14.0),
            ),
            1.0,
        );

    row.padding(10.0)
        .background(Painter::new(|ctx, _: &Todo, _env| {
            let rect = ctx.size().to_rect().to_rounded_rect(4.0);
            ctx.fill(rect, &ITEM_BG);
        }))
        .padding(Insets::new(0.0, 0.0, 0.0, 5.0))
}