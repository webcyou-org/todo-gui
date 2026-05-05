package ui

import (
	"image/color"

	"fyne.io/fyne/v2"
	"fyne.io/fyne/v2/canvas"
	"fyne.io/fyne/v2/widget"

	"github.com/webcyou-org/todo-gui/tree/main/Go/Fyne/apptheme"
	"github.com/webcyou-org/todo-gui/tree/main/Go/Fyne/data"
)

type TodoRow struct {
	widget.BaseWidget
	todo     *data.Todo
	onToggle func(*data.Todo)
}

func NewTodoRow(todo *data.Todo, onToggle func(*data.Todo)) *TodoRow {
	r := &TodoRow{todo: todo, onToggle: onToggle}
	r.ExtendBaseWidget(r)
	return r
}

func (r *TodoRow) CreateRenderer() fyne.WidgetRenderer {
	bg := canvas.NewRectangle(apptheme.ColorSurface)
	bg.CornerRadius = 4

	check := NewCircleCheck(r.todo.IsCompleted)

	textColor := apptheme.ColorText
	if r.todo.IsCompleted {
		textColor = apptheme.ColorMuted
	}
	label := canvas.NewText(r.todo.Task, textColor)
	label.TextSize = 14
	label.Alignment = fyne.TextAlignLeading

	strike := canvas.NewLine(color.Transparent)
	strike.StrokeWidth = 1
	if r.todo.IsCompleted {
		strike.StrokeColor = apptheme.ColorMuted
	}

	return &todoRowRenderer{bg: bg, check: check, label: label, strike: strike}
}

func (r *TodoRow) MinSize() fyne.Size        { return fyne.NewSize(0, 35) }
func (r *TodoRow) Tapped(_ *fyne.PointEvent) { r.onToggle(r.todo) }

type todoRowRenderer struct {
	bg     *canvas.Rectangle
	check  *CircleCheck
	label  *canvas.Text
	strike *canvas.Line
}

func (r *todoRowRenderer) Layout(size fyne.Size) {
	r.bg.Move(fyne.NewPos(0, 0))
	r.bg.Resize(size)

	const cbSize = float32(16)
	const padL = float32(10)
	const padR = float32(10)
	const gap = float32(18)

	cbY := (size.Height - cbSize) / 2
	r.check.Move(fyne.NewPos(padL, cbY))
	r.check.Resize(fyne.NewSize(cbSize, cbSize))

	labelX := padL + cbSize + gap
	labelW := size.Width - labelX - padR
	textH := r.label.TextSize * 1.4
	textY := (size.Height - textH) / 2
	r.label.Move(fyne.NewPos(labelX, textY))
	r.label.Resize(fyne.NewSize(labelW, textH))

	midY := size.Height / 2
	r.strike.Position1 = fyne.NewPos(labelX, midY)
	r.strike.Position2 = fyne.NewPos(labelX+labelW, midY)
}

func (r *todoRowRenderer) MinSize() fyne.Size { return fyne.NewSize(0, 35) }
func (r *todoRowRenderer) Refresh() {
	canvas.Refresh(r.bg)
	r.check.Refresh()
	canvas.Refresh(r.label)
	canvas.Refresh(r.strike)
}
func (r *todoRowRenderer) Destroy() {}
func (r *todoRowRenderer) Objects() []fyne.CanvasObject {
	return []fyne.CanvasObject{r.bg, r.check, r.label, r.strike}
}