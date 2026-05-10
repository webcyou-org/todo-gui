package ui

import (
	"image"

	"gioui.org/layout"
	"gioui.org/op/clip"
	"gioui.org/op/paint"
	"gioui.org/unit"
	"gioui.org/widget"
	"gioui.org/widget/material"

	"github.com/webcyou-org/todo-gui/tree/main/Go/Gio/theme"
)

func LayoutInput(gtx C, th *material.Theme, editor *widget.Editor) D {
	height := gtx.Dp(unit.Dp(35))
	gtx.Constraints.Min.Y = height
	gtx.Constraints.Max.Y = height

	width := gtx.Constraints.Max.X
	r := gtx.Dp(unit.Dp(4))
	rect := image.Rectangle{Max: image.Pt(width, height)}
	focused := gtx.Source.Focused(editor)

	if focused {
		paint.FillShape(gtx.Ops, theme.ColorAccent,
			clip.RRect{Rect: rect, SE: r, SW: r, NE: r, NW: r}.Op(gtx.Ops))
		inner := image.Rectangle{Min: image.Pt(1, 1), Max: image.Pt(width-1, height-1)}
		paint.FillShape(gtx.Ops, theme.ColorInput,
			clip.RRect{Rect: inner, SE: r, SW: r, NE: r, NW: r}.Op(gtx.Ops))
	} else {
		paint.FillShape(gtx.Ops, theme.ColorInput,
			clip.RRect{Rect: rect, SE: r, SW: r, NE: r, NW: r}.Op(gtx.Ops))
	}

	defer clip.RRect{Rect: rect, SE: r, SW: r, NE: r, NW: r}.Push(gtx.Ops).Pop()

	return layout.Inset{
		Top: unit.Dp(4), Bottom: unit.Dp(4),
		Left: unit.Dp(16), Right: unit.Dp(16),
	}.Layout(gtx, func(gtx C) D {
		e := material.Editor(th, editor, "Add Task")
		e.Color = theme.ColorWhite
		e.HintColor = theme.ColorMuted
		e.TextSize = unit.Sp(14)
		return e.Layout(gtx)
	})
}