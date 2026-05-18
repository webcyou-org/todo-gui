use azul::prelude::*;
use azul::widgets::{TextInput, TextInputState, OnTextInputReturn, TextInputValid};
use azul::dom::VirtualKeyCode;
use azul::str::String as AzString;
use azul::css::{
    ColorU, CssProperty, CssPropertyWithConditions,
    LayoutPosition, LayoutFlexGrow, LayoutHeight, LayoutOverflow, LayoutJustifyContent,
    LayoutDisplay, PixelValue, StyleTextColor, StyleFontSize, BorderStyle,
    StyleBackgroundContent,
    StyleBorderTopColor, StyleBorderRightColor, StyleBorderBottomColor, StyleBorderLeftColor,
    StyleBorderTopStyle, StyleBorderRightStyle, StyleBorderBottomStyle, StyleBorderLeftStyle,
    StyleBorderTopLeftRadius, StyleBorderTopRightRadius,
    StyleBorderBottomLeftRadius, StyleBorderBottomRightRadius,
    LayoutBorderTopWidth, LayoutBorderRightWidth, LayoutBorderBottomWidth, LayoutBorderLeftWidth,
    LayoutPaddingTop, LayoutPaddingBottom, LayoutPaddingLeft, LayoutPaddingRight,
};
use azul::vec::{CssPropertyWithConditionsVec, StyleBackgroundContentVec};
use azul::window::StyleCursor;
use crate::data::AppState;

extern "C" fn on_text_input(
    mut data: RefAny,
    _info: CallbackInfo,
    state: TextInputState,
) -> OnTextInputReturn {
    let ret = OnTextInputReturn { update: Update::DoNothing, valid: TextInputValid::Yes };
    if let Some(mut app) = data.downcast_mut::<AppState>() {
        app.input_text = state.get_text().into_string();
    }
    ret
}

extern "C" fn on_key_down(
    mut data: RefAny,
    info: CallbackInfo,
    state: TextInputState,
) -> OnTextInputReturn {
    let ret = OnTextInputReturn { update: Update::DoNothing, valid: TextInputValid::Yes };
    let key = match info.get_current_keyboard_state().current_virtual_keycode.into_option() {
        Some(k) => k,
        None => return ret,
    };
    if key != VirtualKeyCode::Return {
        return ret;
    }
    let text = state.get_text().into_string();
    if text.trim().is_empty() {
        return ret;
    }
    if let Some(mut app) = data.downcast_mut::<AppState>() {
        app.add_todo(text);
        app.input_text = String::new();
    }
    OnTextInputReturn { update: Update::RefreshDom, valid: TextInputValid::Yes }
}

fn mk(r: u8, g: u8, b: u8) -> ColorU { ColorU { r, g, b, a: 255 } }

fn css_props(items: Vec<CssPropertyWithConditions>) -> CssPropertyWithConditionsVec {
    CssPropertyWithConditionsVec::copy_from_ptr(&items[0], items.len())
}

fn input_container_style() -> CssPropertyWithConditionsVec {
    let bg = StyleBackgroundContentVec::from_item(StyleBackgroundContent::color(mk(48, 48, 48)));
    let acc = mk(93, 194, 175);
    css_props(vec![
        CssPropertyWithConditions::simple(CssProperty::position(LayoutPosition::relative())),
        CssPropertyWithConditions::simple(CssProperty::cursor(StyleCursor::text())),
        CssPropertyWithConditions::simple(CssProperty::flex_grow(LayoutFlexGrow::create(0.0))),
        CssPropertyWithConditions::simple(CssProperty::height(LayoutHeight::px(PixelValue::px(35.0)))),
        CssPropertyWithConditions::simple(CssProperty::background_content(bg)),
        CssPropertyWithConditions::simple(CssProperty::text_color(StyleTextColor { inner: mk(255, 255, 255) })),
        CssPropertyWithConditions::simple(CssProperty::overflow_x(LayoutOverflow::hidden())),
        CssPropertyWithConditions::simple(CssProperty::overflow_y(LayoutOverflow::hidden())),
        CssPropertyWithConditions::simple(CssProperty::justify_content(LayoutJustifyContent::center())),
        CssPropertyWithConditions::simple(CssProperty::border_top_left_radius(StyleBorderTopLeftRadius { inner: PixelValue::px(4.0) })),
        CssPropertyWithConditions::simple(CssProperty::border_top_right_radius(StyleBorderTopRightRadius { inner: PixelValue::px(4.0) })),
        CssPropertyWithConditions::simple(CssProperty::border_bottom_left_radius(StyleBorderBottomLeftRadius { inner: PixelValue::px(4.0) })),
        CssPropertyWithConditions::simple(CssProperty::border_bottom_right_radius(StyleBorderBottomRightRadius { inner: PixelValue::px(4.0) })),
        CssPropertyWithConditions::simple(CssProperty::padding_top(LayoutPaddingTop { inner: PixelValue::px(4.0) })),
        CssPropertyWithConditions::simple(CssProperty::padding_bottom(LayoutPaddingBottom { inner: PixelValue::px(4.0) })),
        CssPropertyWithConditions::simple(CssProperty::padding_left(LayoutPaddingLeft { inner: PixelValue::px(16.0) })),
        CssPropertyWithConditions::simple(CssProperty::padding_right(LayoutPaddingRight { inner: PixelValue::px(16.0) })),
        CssPropertyWithConditions::on_focus(CssProperty::border_top_color(StyleBorderTopColor { inner: acc })),
        CssPropertyWithConditions::on_focus(CssProperty::border_right_color(StyleBorderRightColor { inner: acc })),
        CssPropertyWithConditions::on_focus(CssProperty::border_bottom_color(StyleBorderBottomColor { inner: acc })),
        CssPropertyWithConditions::on_focus(CssProperty::border_left_color(StyleBorderLeftColor { inner: acc })),
        CssPropertyWithConditions::on_focus(CssProperty::border_top_width(LayoutBorderTopWidth { inner: PixelValue::px(1.0) })),
        CssPropertyWithConditions::on_focus(CssProperty::border_right_width(LayoutBorderRightWidth { inner: PixelValue::px(1.0) })),
        CssPropertyWithConditions::on_focus(CssProperty::border_bottom_width(LayoutBorderBottomWidth { inner: PixelValue::px(1.0) })),
        CssPropertyWithConditions::on_focus(CssProperty::border_left_width(LayoutBorderLeftWidth { inner: PixelValue::px(1.0) })),
        CssPropertyWithConditions::on_focus(CssProperty::border_top_style(StyleBorderTopStyle { inner: BorderStyle::solid() })),
        CssPropertyWithConditions::on_focus(CssProperty::border_right_style(StyleBorderRightStyle { inner: BorderStyle::solid() })),
        CssPropertyWithConditions::on_focus(CssProperty::border_bottom_style(StyleBorderBottomStyle { inner: BorderStyle::solid() })),
        CssPropertyWithConditions::on_focus(CssProperty::border_left_style(StyleBorderLeftStyle { inner: BorderStyle::solid() })),
    ])
}

fn input_label_style() -> CssPropertyWithConditionsVec {
    css_props(vec![
        CssPropertyWithConditions::simple(CssProperty::display(LayoutDisplay::inline_block())),
        CssPropertyWithConditions::simple(CssProperty::flex_grow(LayoutFlexGrow::create(0.0))),
        CssPropertyWithConditions::simple(CssProperty::position(LayoutPosition::relative())),
        CssPropertyWithConditions::simple(CssProperty::font_size(StyleFontSize::px(14.0))),
        CssPropertyWithConditions::simple(CssProperty::text_color(StyleTextColor { inner: mk(255, 255, 255) })),
    ])
}

fn input_placeholder_style() -> CssPropertyWithConditionsVec {
    css_props(vec![
        CssPropertyWithConditions::simple(CssProperty::display(LayoutDisplay::block())),
        CssPropertyWithConditions::simple(CssProperty::flex_grow(LayoutFlexGrow::create(0.0))),
        CssPropertyWithConditions::simple(CssProperty::position(LayoutPosition::absolute())),
        CssPropertyWithConditions::simple(CssProperty::font_size(StyleFontSize::px(14.0))),
        CssPropertyWithConditions::simple(CssProperty::text_color(StyleTextColor { inner: mk(155, 155, 155) })),
    ])
}

pub fn build_input(state: &AppState, data: RefAny) -> Dom {
    let mut input = TextInput::create()
        .with_text(AzString::from(state.input_text.as_str()))
        .with_placeholder(AzString::from("Add Task"))
        .with_on_text_input(data.clone(), on_text_input)
        .with_on_virtual_key_down(data, on_key_down);

    input.container_style   = input_container_style();
    input.label_style       = input_label_style();
    input.placeholder_style = input_placeholder_style();

    input.dom()
        .with_inline_style("margin-bottom: 14px; width: 100%;")
}