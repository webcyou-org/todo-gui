package main

import (
	"strings"

	"fyne.io/fyne/v2"
	"fyne.io/fyne/v2/app"
	"fyne.io/fyne/v2/canvas"
	"fyne.io/fyne/v2/container"
	"fyne.io/fyne/v2/layout"
	"fyne.io/fyne/v2/widget"

	"github.com/webcyou-org/todo-gui/tree/main/Go/Fyne/apptheme"
	"github.com/webcyou-org/todo-gui/tree/main/Go/Fyne/data"
	"github.com/webcyou-org/todo-gui/tree/main/Go/Fyne/ui"
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

func buildUI(_ fyne.Window, todoModel *data.TodoModel, menuModel *data.MenuModel) fyne.CanvasObject {
	title := canvas.NewText("ToDo", apptheme.ColorWhite)
	title.TextSize = 18
	title.TextStyle = fyne.TextStyle{Bold: true}

	entry := widget.NewEntry()
	entry.SetPlaceHolder("Add Task")

	tabsBox := container.NewHBox()
	listBox := container.NewVBox()
	scroll := container.NewVScroll(listBox)

	var refreshTabs, refreshList func()

	refreshList = func() {
		listBox.Objects = nil
		for _, todo := range todoModel.GetFilteredTodos(menuModel.GetActiveTab()) {
			todo := todo
			listBox.Add(ui.NewTodoRow(todo, func(t *data.Todo) {
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
			tabsBox.Add(ui.NewTabButton(tab, tab == active, func(t data.TabFilter) {
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