package main

import (
	"image/color"
	"strings"

	"fyne.io/fyne/v2"
	"fyne.io/fyne/v2/app"
	"fyne.io/fyne/v2/canvas"
	"fyne.io/fyne/v2/container"
	"fyne.io/fyne/v2/layout"
	"fyne.io/fyne/v2/widget"

	"github.com/webcyou-org/todo-gui/tree/main/Go/Fyne/apptheme"
	"github.com/webcyou-org/todo-gui/tree/main/Go/Fyne/data"
)

func main() {
	a := app.New()
	a.Settings().SetTheme(&apptheme.AppTheme{})

	w := a.NewWindow("ToDo")
	w.Resize(fyne.NewSize(800, 600))

	todoModel := data.NewTodoModel()
	menuModel := data.NewMenuModel()

	w.SetContent(buildUI(w, todoModel, menuModel))
	w.ShowAndRun()
}

func buildUI(w fyne.Window, todoModel *data.TodoModel, menuModel *data.MenuModel) fyne.CanvasObject {
	title := canvas.NewText("ToDo", apptheme.ColorWhite)
	title.TextSize = 18
	title.TextStyle = fyne.TextStyle{Bold: true}

	// ── Input ──────────────────────────────────────────────────────────────────
	entry := widget.NewEntry()
	entry.SetPlaceHolder("Add Task")

	// ── Tabs ───────────────────────────────────────────────────────────────────
	tabsBox := container.NewHBox()

	// ── List ───────────────────────────────────────────────────────────────────
	listBox := container.NewVBox()
	scroll := container.NewVScroll(listBox)

	// mutual closures
	var refreshTabs, refreshList func()

	refreshList = func() {
		listBox.Objects = nil
		todos := todoModel.GetFilteredTodos(menuModel.GetActiveTab())
		for _, todo := range todos {
			todo := todo
			listBox.Add(newTodoRow(todo, func(t *data.Todo) {
				todoModel.ChangeCompleted(t)
				refreshList()
			}))
		}
		listBox.Refresh()
		scroll.Refresh()
	}

	refreshTabs = func() {
		tabsBox.Objects = nil
		active := menuModel.GetActiveTab()
		for _, tab := range menuModel.GetTabList() {
			tab := tab
			tabsBox.Add(newTabButton(tab, tab == active, func(t data.TabFilter) {
				menuModel.SetActiveTab(t)
				refreshTabs()
				refreshList()
			}))
		}
		tabsBox.Refresh()
	}

	entry.OnSubmitted = func(text string) {
		task := strings.TrimSpace(text)
		if task == "" {
			return
		}
		todoModel.AddTodo(task)
		entry.SetText("")
		refreshList()
	}

	refreshTabs()
	refreshList()

	content := container.NewBorder(
		container.NewVBox(title, entry, tabsBox),
		nil, nil, nil,
		scroll,
	)

	return container.New(
		layout.NewCustomPaddedLayout(10, 10, 24, 24),
		content,
	)
}

// ── tabButton ──────────────────────────────────────────────────────────────────

type tabButton struct {
	widget.BaseWidget
	tab    data.TabFilter
	active bool
	onTap  func(data.TabFilter)
}

func newTabButton(tab data.TabFilter, active bool, onTap func(data.TabFilter)) *tabButton {
	b := &tabButton{tab: tab, active: active, onTap: onTap}
	b.ExtendBaseWidget(b)
	return b
}

func (b *tabButton) CreateRenderer() fyne.WidgetRenderer {
	text := canvas.NewText(b.tab.Label(), apptheme.ColorText)
	text.TextSize = 14
	text.TextStyle = fyne.TextStyle{Bold: b.active}
	return widget.NewSimpleRenderer(
		container.New(layout.NewCustomPaddedLayout(0, 0, 8, 8), text),
	)
}

func (b *tabButton) Tapped(_ *fyne.PointEvent) { b.onTap(b.tab) }

// ── circleCheck ────────────────────────────────────────────────────────────────

type circleCheck struct {
	widget.BaseWidget
	checked bool
}

func newCircleCheck(checked bool) *circleCheck {
	c := &circleCheck{checked: checked}
	c.ExtendBaseWidget(c)
	return c
}

func (c *circleCheck) CreateRenderer() fyne.WidgetRenderer {
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
	check  *circleCheck
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
		r.circle.FillColor = apptheme.ColorAccent
		r.circle.StrokeColor = apptheme.ColorAccent
		r.circle.StrokeWidth = 0
		r.line1.StrokeColor = apptheme.ColorWhite
		r.line2.StrokeColor = apptheme.ColorWhite
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

// ── todoRow ────────────────────────────────────────────────────────────────────

type todoRow struct {
	widget.BaseWidget
	todo     *data.Todo
	onToggle func(*data.Todo)
}

func newTodoRow(todo *data.Todo, onToggle func(*data.Todo)) *todoRow {
	r := &todoRow{todo: todo, onToggle: onToggle}
	r.ExtendBaseWidget(r)
	return r
}

func (r *todoRow) CreateRenderer() fyne.WidgetRenderer {
	bg := canvas.NewRectangle(apptheme.ColorSurface)
	bg.CornerRadius = 4

	check := newCircleCheck(r.todo.IsCompleted)

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

func (r *todoRow) MinSize() fyne.Size        { return fyne.NewSize(0, 35) }
func (r *todoRow) Tapped(_ *fyne.PointEvent) { r.onToggle(r.todo) }

type todoRowRenderer struct {
	bg     *canvas.Rectangle
	check  *circleCheck
	label  *canvas.Text
	strike *canvas.Line
}

func (r *todoRowRenderer) Layout(size fyne.Size) {
	r.bg.Move(fyne.NewPos(0, 0))
	r.bg.Resize(size)

	const cbSize = float32(16)
	const padL = float32(10)
	const padR = float32(10)
	const gap = float32(8)

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