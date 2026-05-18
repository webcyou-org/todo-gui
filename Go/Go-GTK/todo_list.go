package main

import (
	"github.com/mattn/go-gtk/gdk"
	"github.com/mattn/go-gtk/gtk"
)

func (app *App) buildList() *gtk.ScrolledWindow {
	scroll := gtk.NewScrolledWindow(nil, nil)
	scroll.SetPolicy(gtk.POLICY_NEVER, gtk.POLICY_AUTOMATIC)
	scroll.SetShadowType(gtk.SHADOW_NONE)

	viewport := gtk.NewViewport(nil, nil)
	viewport.SetShadowType(gtk.SHADOW_NONE)
	viewport.ModifyBG(gtk.STATE_NORMAL, color(C_BG))

	app.viewport = viewport
	scroll.Add(viewport)

	return scroll
}

func (app *App) refreshList() {
	if app.listContainer != nil {
		app.viewport.Remove(app.listContainer)
		app.listContainer.Destroy()
	}

	app.listContainer = gtk.NewVBox(false, 0)

	active := app.menuModel.GetActiveTab()
	todos := app.todoModel.GetFilteredTodos(active)

	for _, todo := range todos {
		item := app.buildTodoItem(todo)
		app.listContainer.PackStart(item, false, false, 0)
	}

	app.viewport.Add(app.listContainer)
	app.listContainer.ShowAll()
}

func (app *App) buildTodoItem(todo Todo) *gtk.Alignment {
	outerAlign := gtk.NewAlignment(0, 0, 1, 1)
	outerAlign.SetPadding(0, 5, 0, 0)

	itemEB := gtk.NewEventBox()
	itemEB.ModifyBG(gtk.STATE_NORMAL, color(C_SURFACE))
	itemEB.ModifyBG(gtk.STATE_PRELIGHT, color(C_SURFACE))
	itemEB.SetSizeRequest(-1, 35)

	innerAlign := gtk.NewAlignment(0.5, 0.5, 1, 1)
	innerAlign.SetPadding(0, 0, 10, 10)

	hbox := gtk.NewHBox(false, 0)

	checkbox := app.makeCheckbox(todo)
	hbox.PackStart(checkbox, false, false, 0)

	spacer := gtk.NewLabel("")
	spacer.SetSizeRequest(18, -1)
	hbox.PackStart(spacer, false, false, 0)

	textLabel := gtk.NewLabel("")
	textLabel.SetAlignment(0, 0.5)
	textLabel.ModifyFontEasy("Sans 10.5")

	if todo.IsCompleted {
		textLabel.SetMarkup("<s>" + todo.Task + "</s>")
		textLabel.ModifyFG(gtk.STATE_NORMAL, color(C_MUTED))
	} else {
		textLabel.SetText(todo.Task)
		textLabel.ModifyFG(gtk.STATE_NORMAL, color(C_TEXT))
	}

	hbox.PackStart(textLabel, true, true, 0)

	innerAlign.Add(hbox)
	itemEB.Add(innerAlign)
	outerAlign.Add(itemEB)

	return outerAlign
}

func (app *App) makeCheckbox(todo Todo) *gtk.DrawingArea {
	da := gtk.NewDrawingArea()
	da.SetSizeRequest(16, 16)
	da.ModifyBG(gtk.STATE_NORMAL, color(C_SURFACE))

	id := todo.ID

	da.Connect("expose-event", func() {
		win := da.GetWindow()
		if win == nil {
			return
		}
		d := win.GetDrawable()
		gc := gdk.NewGC(d)

		t := app.todoModel.FindByID(id)
		if t == nil {
			return
		}

		if t.IsCompleted {
			// Outlined circle in CB border color
			gc.SetRgbFgColor(color(C_CB_BORDER))
			d.DrawArc(gc, false, 0, 0, 15, 15, 0, 360*64)
			// Checkmark in accent
			d.DrawLine(gc, 4, 8, 7, 11)
			d.DrawLine(gc, 7, 11, 12, 5)
		} else {
			// Outer ring: fill with border color
			gc.SetRgbFgColor(color(C_CB_BORDER))
			d.DrawArc(gc, true, 0, 0, 16, 16, 0, 360*64)
			// Inner fill: surface color to create 2px ring appearance
			gc.SetRgbFgColor(color(C_SURFACE))
			d.DrawArc(gc, true, 2, 2, 12, 12, 0, 360*64)
		}
	})

	da.AddEvents(int(gdk.BUTTON_PRESS_MASK))
	da.Connect("button-press-event", func() bool {
		app.todoModel.ChangeCompleted(id)
		app.refreshList()
		return true
	})

	return da
}