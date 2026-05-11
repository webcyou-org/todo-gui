package main

import (
	"github.com/mattn/go-gtk/gdk"
	"github.com/mattn/go-gtk/gtk"
)

func (app *App) buildTabs() *gtk.Alignment {
	hbox := gtk.NewHBox(false, 0)
	app.tabLabels = make(map[TabFilter]*gtk.Label)

	for _, tab := range app.menuModel.GetTabList() {
		t := tab

		label := gtk.NewLabel(string(t))
		label.SetSizeRequest(-1, 28)
		app.tabLabels[t] = label

		eb := gtk.NewEventBox()
		eb.ModifyBG(gtk.STATE_NORMAL, color(C_BG))
		eb.ModifyBG(gtk.STATE_PRELIGHT, color(C_BG))

		padAlign := gtk.NewAlignment(0, 0.5, 1, 1)
		padAlign.SetPadding(0, 0, 8, 8)
		padAlign.Add(label)
		eb.Add(padAlign)

		eb.AddEvents(int(gdk.BUTTON_PRESS_MASK))
		eb.Connect("button-press-event", func() bool {
			app.menuModel.SetActiveTab(t)
			app.updateTabLabels()
			app.refreshList()
			return false
		})

		hbox.PackStart(eb, false, false, 0)
	}

	app.updateTabLabels()

	a := gtk.NewAlignment(0, 0, 1, 1)
	a.SetPadding(0, 3, 0, 0)
	a.Add(hbox)
	return a
}

func (app *App) updateTabLabels() {
	active := app.menuModel.GetActiveTab()
	for tab, label := range app.tabLabels {
		if tab == active {
			label.ModifyFontEasy("Sans Bold 10.5")
		} else {
			label.ModifyFontEasy("Sans 10.5")
		}
		label.ModifyFG(gtk.STATE_NORMAL, color(C_TEXT))
	}
}