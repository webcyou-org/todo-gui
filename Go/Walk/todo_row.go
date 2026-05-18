package main

import (
	"github.com/lxn/walk"
)

var (
	rowNormalFont *walk.Font
	rowStrikeFont *walk.Font
)

func ensureRowFonts() error {
	if rowNormalFont != nil {
		return nil
	}
	var err error
	rowNormalFont, err = walk.NewFont("Segoe UI", 10, 0)
	if err != nil {
		return err
	}
	rowStrikeFont, err = walk.NewFont("Segoe UI", 10, walk.FontStrikeOut)
	return err
}

// newTodoRow creates a custom-painted todo row widget inside parent.
func newTodoRow(parent walk.Container, todo *Todo, onToggle func(*Todo)) (*walk.CustomWidget, error) {
	if err := ensureRowFonts(); err != nil {
		return nil, err
	}

	var cw *walk.CustomWidget
	var err error
	cw, err = walk.NewCustomWidget(parent, 0, func(canvas *walk.Canvas, updateBounds walk.Rectangle) error {
		return paintTodoRow(canvas, cw.ClientBounds(), todo)
	})
	if err != nil {
		return nil, err
	}

	if err := cw.SetMinMaxSize(walk.Size{Width: 430, Height: 35}, walk.Size{Width: 0, Height: 35}); err != nil {
		return nil, err
	}

	cw.MouseDown().Attach(func(x, y int, button walk.MouseButton) {
		if button == walk.LeftButton {
			onToggle(todo)
		}
	})

	return cw, nil
}

func paintTodoRow(canvas *walk.Canvas, bounds walk.Rectangle, todo *Todo) error {
	// Background (flat rect — Walk Canvas has no rounded rect API)
	bgBrush, err := walk.NewSolidColorBrush(colorSurface)
	if err != nil {
		return err
	}
	defer bgBrush.Dispose()
	if err := canvas.FillRectangle(bgBrush, bounds); err != nil {
		return err
	}

	const cbSize = 16
	const padL = 10
	cbY := (bounds.Height - cbSize) / 2
	cbBounds := walk.Rectangle{X: padL, Y: cbY, Width: cbSize, Height: cbSize}

	if todo.IsCompleted {
		// Circle outline in CB border color (outer fill + inner surface cutout)
		borderBrush, _ := walk.NewSolidColorBrush(colorCBBorder)
		defer borderBrush.Dispose()
		bgInner, _ := walk.NewSolidColorBrush(colorSurface)
		defer bgInner.Dispose()
		canvas.FillEllipse(borderBrush, cbBounds)
		canvas.FillEllipse(bgInner, walk.Rectangle{
			X: padL + 2, Y: cbY + 2, Width: cbSize - 4, Height: cbSize - 4,
		})

		// Checkmark in accent color
		checkPen, _ := walk.NewCosmeticPen(walk.PenSolid, colorAccent)
		defer checkPen.Dispose()
		canvas.DrawPolyline(checkPen, []walk.Point{
			{X: padL + 4, Y: cbY + 8},
			{X: padL + 7, Y: cbY + 11},
			{X: padL + 12, Y: cbY + 5},
		})
	} else {
		// Bordered circle: outer (border) then inner (bg) ellipse
		borderBrush, _ := walk.NewSolidColorBrush(colorCBBorder)
		defer borderBrush.Dispose()
		bgInner, _ := walk.NewSolidColorBrush(colorSurface)
		defer bgInner.Dispose()
		canvas.FillEllipse(borderBrush, cbBounds)
		canvas.FillEllipse(bgInner, walk.Rectangle{
			X: padL + 2, Y: cbY + 2, Width: cbSize - 4, Height: cbSize - 4,
		})
	}

	// Text label: padL(10) + cbSize(16) + cbMarginRight(18) = 44
	const labelX = 44
	const padR = 10
	labelBounds := walk.Rectangle{
		X: labelX, Y: 0,
		Width:  bounds.Width - labelX - padR,
		Height: bounds.Height,
	}

	textColor := colorText
	font := rowNormalFont
	if todo.IsCompleted {
		textColor = colorMuted
		font = rowStrikeFont
	}

	return canvas.DrawText(
		todo.Task, font, textColor, labelBounds,
		walk.TextLeft|walk.TextVCenter|walk.TextSingleLine,
	)
}