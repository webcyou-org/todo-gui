package main

import (
	"os"
	"strings"

	"github.com/therecipe/qt/core"
	"github.com/therecipe/qt/gui"
	"github.com/therecipe/qt/widgets"
)

type MainWindow struct {
	widget    *widgets.QWidget
	input     *widgets.QLineEdit
	tabMenu   *TabMenu
	todoList  *TodoList
	todoModel *TodoModel
	menuModel *MenuModel
}

func newMainWindow() *MainWindow {
	mw := &MainWindow{
		todoModel: newTodoModel(),
		menuModel: &MenuModel{ActiveTab: TabAll},
	}

	mw.widget = widgets.NewQWidget(nil, core.Qt__Window)
	mw.widget.SetWindowTitle("ToDo")
	mw.widget.SetFixedSize2(800, 600)

	pal := mw.widget.Palette()
	pal.SetColor2(gui.QPalette__Window, T.BG)
	mw.widget.SetPalette(pal)
	mw.widget.SetAutoFillBackground(true)

	root := widgets.NewQVBoxLayout2(mw.widget)
	root.SetContentsMargins(contentH, contentV, contentH, contentV)
	root.SetSpacing(0)

	// Title
	title := widgets.NewQLabel2("ToDo", nil, core.Qt__Widget)
	tf := gui.NewQFont()
	tf.SetPixelSize(18)
	tf.SetBold(true)
	title.SetFont(tf)
	tp := title.Palette()
	tp.SetColor2(gui.QPalette__WindowText, T.White)
	title.SetPalette(tp)
	root.AddWidget(title, 0, 0)
	root.AddSpacing(14)

	// Input
	mw.input = newTodoInput()
	mw.input.ConnectReturnPressed(mw.onAddTodo)
	root.AddWidget(mw.input, 0, 0)
	root.AddSpacing(14)

	// Tabs
	mw.tabMenu = newTabMenu(mw.onTabClicked)
	root.AddWidget(mw.tabMenu.Widget, 0, 0)
	root.AddSpacing(3)

	// List
	mw.todoList = newTodoList(mw.onToggle)
	root.AddWidget(mw.todoList.Widget, 1, 0)

	mw.refreshList()
	mw.refreshTabs()

	return mw
}

func (mw *MainWindow) onAddTodo() {
	text := strings.TrimSpace(mw.input.Text())
	if text == "" {
		return
	}
	mw.todoModel.AddTodo(text)
	mw.input.SetText("")
	mw.refreshList()
}

func (mw *MainWindow) onToggle(id int) {
	mw.todoModel.ToggleCompleted(id)
	mw.refreshList()
}

func (mw *MainWindow) onTabClicked(tab TabFilter) {
	mw.menuModel.ActiveTab = tab
	mw.refreshTabs()
	mw.refreshList()
}

func (mw *MainWindow) refreshList() {
	mw.todoList.Refresh(mw.todoModel.FilteredTodos(mw.menuModel.ActiveTab))
}

func (mw *MainWindow) refreshTabs() {
	mw.tabMenu.SetActive(mw.menuModel.ActiveTab)
}

func main() {
	app := widgets.NewQApplication(len(os.Args), os.Args)
	initTheme()
	mw := newMainWindow()
	mw.widget.Show()
	app.Exec()
}