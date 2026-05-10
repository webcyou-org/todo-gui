package ui

import (
	"image"

	"gioui.org/layout"
	"gioui.org/op/clip"
	"gioui.org/op/paint"
	"gioui.org/unit"
	"gioui.org/widget"
	"gioui.org/widget/material"

	"github.com/webcyou-org/todo-gui/tree/main/Go/Gio/data"
	"github.com/webcyou-org/todo-gui/tree/main/Go/Gio/theme"
)

type (
	C = layout.Context
	D = layout.Dimensions
)

func LayoutList(gtx C, th *material.Theme, list *layout.List, todos []*data.Todo, clicks map[int]*widget.Clickable) D {
	return list.Layout(gtx, len(todos), func(gtx C, i int) D {
		todo := todos[i]
		click := clicks[todo.ID]
		return layout.Flex{Axis: layout.Vertical}.Layout(gtx,
			layout.Rigid(func(gtx C) D {
				return layoutTodoItem(gtx, th, todo, click)
			}),
			layout.Rigid(layout.Spacer{Height: unit.Dp(5)}.Layout),
		)
	})
}

func layoutTodoItem(gtx C, th *material.Theme, todo *data.Todo, click *widget.Clickable) D {
	height := gtx.Dp(unit.Dp(35))
	gtx.Constraints.Min.Y = height
	gtx.Constraints.Max.Y = height

	width := gtx.Constraints.Max.X
	r := gtx.Dp(unit.Dp(4))
	rect := image.Rectangle{Max: image.Pt(width, height)}

	paint.FillShape(gtx.Ops, theme.ColorSurface,
		clip.RRect{Rect: rect, SE: r, SW: r, NE: r, NW: r}.Op(gtx.Ops))

	defer clip.RRect{Rect: rect, SE: r, SW: r, NE: r, NW: r}.Push(gtx.Ops).Pop()

	return layout.UniformInset(unit.Dp(10)).Layout(gtx, func(gtx C) D {
		return layout.Flex{Axis: layout.Horizontal, Alignment: layout.Middle}.Layout(gtx,
			layout.Rigid(func(gtx C) D {
				return click.Layout(gtx, func(gtx C) D {
					return drawCheckbox(gtx, todo.IsCompleted)
				})
			}),
			layout.Rigid(layout.Spacer{Width: unit.Dp(18)}.Layout),
			layout.Flexed(1, func(gtx C) D {
				return layoutTodoText(gtx, th, todo)
			}),
		)
	})
}

func drawCheckbox(gtx C, checked bool) D {
	size := gtx.Dp(unit.Dp(16))
	ellipse := clip.Ellipse(image.Rectangle{Max: image.Pt(size, size)})

	if checked {
		paint.FillShape(gtx.Ops, theme.ColorAccent, ellipse.Op(gtx.Ops))
	} else {
		paint.FillShape(gtx.Ops, theme.ColorCBBorder, ellipse.Op(gtx.Ops))
		b := gtx.Dp(unit.Dp(2))
		inner := clip.Ellipse(image.Rectangle{Min: image.Pt(b, b), Max: image.Pt(size-b, size-b)})
		paint.FillShape(gtx.Ops, theme.ColorSurface, inner.Op(gtx.Ops))
	}

	return D{Size: image.Pt(size, size)}
}

func layoutTodoText(gtx C, th *material.Theme, todo *data.Todo) D {
	lbl := material.Label(th, unit.Sp(14), todo.Task)
	if todo.IsCompleted {
		lbl.Color = theme.ColorMuted
	} else {
		lbl.Color = theme.ColorText
	}
	dims := lbl.Layout(gtx)
	if todo.IsCompleted {
		mid := dims.Size.Y / 2
		paint.FillShape(gtx.Ops, theme.ColorMuted,
			clip.Rect(image.Rectangle{
				Min: image.Pt(0, mid),
				Max: image.Pt(dims.Size.X, mid+1),
			}).Op())
	}
	return dims
}