package ui

import (
	"image/color"

	"fyne.io/fyne/v2"
	"fyne.io/fyne/v2/canvas"
	"fyne.io/fyne/v2/widget"

	"github.com/webcyou-org/todo-gui/tree/main/Go/Fyne/apptheme"
)

type CircleCheck struct {
	widget.BaseWidget
	checked bool
}

func NewCircleCheck(checked bool) *CircleCheck {
	c := &CircleCheck{checked: checked}
	c.ExtendBaseWidget(c)
	return c
}

func (c *CircleCheck) CreateRenderer() fyne.WidgetRenderer {
	circle := canvas.NewCircle(color.Transparent)
	line1 := canvas.NewLine(color.Transparent)
	line1.StrokeWidth = 1.5
	line2 := canvas.NewLine(color.Transparent)
	line2.StrokeWidth = 1.5
	r := &circleCheckRenderer{check: c, circle: circle, line1: line1, line2: line2}
	r.Refresh()
	return r
}

type circleCheckRenderer struct {
	check  *CircleCheck
	circle *canvas.Circle
	line1  *canvas.Line
	line2  *canvas.Line
}

func (r *circleCheckRenderer) Layout(size fyne.Size) {
	r.circle.Move(fyne.NewPos(0, 0))
	r.circle.Resize(size)
	w, h := size.Width, size.Height
	r.line1.Position1 = fyne.NewPos(w*0.25, h*0.50)
	r.line1.Position2 = fyne.NewPos(w*0.44, h*0.69)
	r.line2.Position1 = fyne.NewPos(w*0.44, h*0.69)
	r.line2.Position2 = fyne.NewPos(w*0.75, h*0.31)
}

func (r *circleCheckRenderer) MinSize() fyne.Size { return fyne.NewSize(16, 16) }

func (r *circleCheckRenderer) Refresh() {
	if r.check.checked {
		r.circle.FillColor = color.Transparent
		r.circle.StrokeColor = apptheme.ColorCBBorder
		r.circle.StrokeWidth = 1.5
		r.line1.StrokeColor = apptheme.ColorAccent
		r.line2.StrokeColor = apptheme.ColorAccent
	} else {
		r.circle.FillColor = color.Transparent
		r.circle.StrokeColor = apptheme.ColorCBBorder
		r.circle.StrokeWidth = 1.5
		r.line1.StrokeColor = color.Transparent
		r.line2.StrokeColor = color.Transparent
	}
}

func (r *circleCheckRenderer) Destroy() {}
func (r *circleCheckRenderer) Objects() []fyne.CanvasObject {
	return []fyne.CanvasObject{r.circle, r.line1, r.line2}
}