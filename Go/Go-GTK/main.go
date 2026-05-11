package main

import (
	"github.com/mattn/go-gtk/glib"
	"github.com/mattn/go-gtk/gtk"
)

// App holds all model and UI state.
type App struct {
	todoModel *TodoModel
	menuModel *MenuModel

	viewport      *gtk.Viewport
	listContainer *gtk.VBox
	tabLabels     map[TabFilter]*gtk.Label

	inputEntry         *gtk.Entry
	inputIsPlaceholder bool
}

func (app *App) buildUI(win *gtk.Window) {
	bgEB := gtk.NewEventBox()
	bgEB.ModifyBG(gtk.STATE_NORMAL, color(C_BG))

	contentAlign := gtk.NewAlignment(0, 0, 1, 1)
	contentAlign.SetPadding(10, 10, 24, 24)

	vbox := gtk.NewVBox(false, 0)
	vbox.PackStart(app.buildTitle(), false, false, 0)
	vbox.PackStart(app.buildInput(), false, false, 0)
	vbox.PackStart(app.buildTabs(), false, false, 0)
	vbox.PackStart(app.buildList(), true, true, 0)

	contentAlign.Add(vbox)
	bgEB.Add(contentAlign)
	win.Add(bgEB)

	app.refreshList()
}

func main() {
	gtk.Init(nil)

	app := &App{
		todoModel: NewTodoModel(),
		menuModel: NewMenuModel(),
	}

	win := gtk.NewWindow(gtk.WINDOW_TOPLEVEL)
	win.SetTitle("ToDo")
	win.SetDefaultSize(800, 600)
	win.Connect("destroy", gtk.MainQuit)

	app.buildUI(win)

	win.ShowAll()

	// GTK2 auto-focuses the first focusable widget (Entry) on map, which fires
	// focus-in-event and clears the placeholder. Restore it in the next idle tick
	// after startup focus events have been processed.
	glib.IdleAdd(func() bool {
		if app.inputIsPlaceholder {
			app.inputEntry.SetText("Add Task")
			app.inputEntry.ModifyText(gtk.STATE_NORMAL, color(C_MUTED))
		}
		return false
	})

	gtk.Main()
}