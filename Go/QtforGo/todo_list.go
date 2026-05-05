package main

import (
	"github.com/therecipe/qt/core"
	"github.com/therecipe/qt/gui"
	"github.com/therecipe/qt/widgets"
)

type TodoList struct {
	Widget     *widgets.QScrollArea
	container  *widgets.QWidget
	listLayout *widgets.QVBoxLayout
	onToggle   func(int)
}

func newTodoList(onToggle func(int)) *TodoList {
	tl := &TodoList{onToggle: onToggle}

	tl.Widget = widgets.NewQScrollArea(nil)
	tl.Widget.SetWidgetResizable(true)
	tl.Widget.SetFrameShape(widgets.QFrame__NoFrame)
	tl.Widget.SetHorizontalScrollBarPolicy(core.Qt__ScrollBarAlwaysOff)
	tl.Widget.SetStyleSheet("QScrollArea { background: transparent; border: none; }")
	tl.Widget.Viewport().SetStyleSheet("background: transparent;")

	tl.container = widgets.NewQWidget(nil, core.Qt__Widget)
	tl.container.SetAutoFillBackground(false)
	tl.container.SetStyleSheet("background: transparent;")

	tl.listLayout = widgets.NewQVBoxLayout2(tl.container)
	tl.listLayout.SetContentsMargins(0, 0, 0, 0)
	tl.listLayout.SetSpacing(itemMB)
	tl.listLayout.AddStretch(1)

	tl.Widget.SetWidget(tl.container)
	return tl
}

func (tl *TodoList) Refresh(todos []Todo) {
	for tl.listLayout.Count() > 1 {
		item := tl.listLayout.TakeAt(0)
		if w := item.Widget(); w != nil {
			w.Destroy(false, false)
		}
	}
	for _, todo := range todos {
		t := todo
		row := newTodoItemWidget(tl.container, t, tl.onToggle)
		tl.listLayout.InsertWidget(tl.listLayout.Count()-1, row, 0, 0)
	}
}

func newTodoItemWidget(parent *widgets.QWidget, todo Todo, onToggle func(int)) *widgets.QWidget {
	cbX := cbPadL
	cbY := (itemH - cbSize) / 2
	cbRect := core.NewQRect4(cbX, cbY, cbSize, cbSize)

	w := widgets.NewQWidget(parent, core.Qt__Widget)
	w.SetFixedHeight(itemH)
	w.SetCursor(gui.NewQCursor2(core.Qt__PointingHandCursor))

	w.ConnectPaintEvent(func(event *gui.QPaintEvent) {
		p := gui.NewQPainter2(w)
		defer p.End()
		p.SetRenderHint(gui.QPainter__Antialiasing, true)

		// Background
		p.SetPen3(core.Qt__NoPen)
		p.SetBrush(gui.NewQBrush3(T.Surface, core.Qt__SolidPattern))
		p.DrawRoundedRect3(w.Rect(), 4, 4, core.Qt__AbsoluteSize)

		if todo.IsCompleted {
			// Filled circle
			p.SetBrush(gui.NewQBrush3(T.Accent, core.Qt__SolidPattern))
			p.SetPen3(core.Qt__NoPen)
			p.DrawEllipse2(cbRect)

			// Checkmark
			pen := gui.NewQPen4(
				gui.NewQBrush3(T.White, core.Qt__SolidPattern),
				1.5,
				core.Qt__SolidLine,
				core.Qt__RoundCap,
				core.Qt__RoundJoin,
			)
			p.SetPen(pen)
			cx := float64(cbX + cbSize/2)
			cy := float64(cbY + cbSize/2)
			mark := gui.NewQPolygonF3([]*core.QPointF{
				core.NewQPointF3(cx-4, cy),
				core.NewQPointF3(cx-1, cy+3),
				core.NewQPointF3(cx+4, cy-3),
			})
			p.DrawPolyline2(mark)
		} else {
			// Bordered circle
			p.SetBrush2(core.Qt__NoBrush)
			p.SetPen(gui.NewQPen3(T.CBBorder))
			p.DrawEllipse2(cbRect)
		}

		// Text
		font := gui.NewQFont()
		font.SetPixelSize(14)
		font.SetStrikeOut(todo.IsCompleted)
		p.SetFont(font)
		if todo.IsCompleted {
			p.SetPen2(T.Muted)
		} else {
			p.SetPen2(T.Text)
		}
		textRect := core.NewQRect4(labelX, 0, w.Width()-labelX-contentH, w.Height())
		p.DrawText4(textRect, int(core.Qt__AlignVCenter|core.Qt__AlignLeft), todo.Task, nil)
	})

	w.ConnectMousePressEvent(func(event *gui.QMouseEvent) {
		if cbRect.Contains(event.Pos(), false) {
			onToggle(todo.ID)
		}
	})

	return w
}