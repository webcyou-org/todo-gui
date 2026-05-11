package main

import "github.com/mattn/go-gtk/gtk"

func (app *App) buildTitle() *gtk.Alignment {
	label := gtk.NewLabel("ToDo")
	label.SetAlignment(0, 0.5)
	label.ModifyFontEasy("Sans Bold 13.5")
	label.ModifyFG(gtk.STATE_NORMAL, color(C_WHITE))

	a := gtk.NewAlignment(0, 0, 1, 1)
	a.SetPadding(0, 14, 0, 0)
	a.Add(label)
	return a
}

func (app *App) buildInput() *gtk.Alignment {
	entry := gtk.NewEntry()
	app.inputEntry = entry
	app.inputIsPlaceholder = true

	entry.SetText("Add Task")
	entry.SetSizeRequest(-1, 35)
	entry.ModifyBase(gtk.STATE_NORMAL, color(C_INPUT))
	entry.ModifyBase(gtk.STATE_ACTIVE, color(C_INPUT))
	entry.ModifyBase(gtk.STATE_SELECTED, color(C_ACCENT))
	entry.ModifyText(gtk.STATE_NORMAL, color(C_MUTED))
	entry.ModifyText(gtk.STATE_ACTIVE, color(C_MUTED))
	entry.ModifyText(gtk.STATE_SELECTED, color(C_WHITE))
	entry.ModifyFontEasy("Sans 10.5")

	entry.Connect("focus-in-event", func() bool {
		if app.inputIsPlaceholder {
			entry.SetText("")
			entry.ModifyText(gtk.STATE_NORMAL, color(C_WHITE))
			app.inputIsPlaceholder = false
		}
		return false
	})

	entry.Connect("focus-out-event", func() bool {
		if entry.GetText() == "" {
			entry.SetText("Add Task")
			entry.ModifyText(gtk.STATE_NORMAL, color(C_MUTED))
			app.inputIsPlaceholder = true
		}
		return false
	})

	entry.Connect("activate", func() {
		if app.inputIsPlaceholder {
			return
		}
		text := entry.GetText()
		if text == "" {
			return
		}
		app.todoModel.AddTodo(text)
		entry.SetText("")
		app.refreshList()
	})

	a := gtk.NewAlignment(0, 0, 1, 1)
	a.SetPadding(0, 14, 0, 0)
	a.Add(entry)
	return a
}