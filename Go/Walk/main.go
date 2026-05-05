package main

// Walk is Windows-only. Build on Windows with:
//   go generate   (requires rsrc tool: go install github.com/akavel/rsrc@latest)
//   go build -ldflags="-H windowsgui"
//
//go:generate rsrc -manifest todo.manifest -o rsrc.syso

import (
	"strings"

	"github.com/lxn/walk"
	. "github.com/lxn/walk/declarative"
)

var (
	todoModel = NewTodoModel()
	menuModel = NewMenuModel()
)

func main() {
	var mw *walk.MainWindow
	var inputEdit *walk.LineEdit
	var tabsComposite *walk.Composite
	var listComposite *walk.Composite

	tabFont, _ := walk.NewFont("Segoe UI", 10, 0)
	tabBoldFont, _ := walk.NewFont("Segoe UI", 10, walk.FontBold)
	defer tabFont.Dispose()
	defer tabBoldFont.Dispose()

	var tabLabels []*walk.Label
	var todoRows []*walk.CustomWidget

	var refreshList func()
	var refreshTabs func()

	refreshList = func() {
		listComposite.SetSuspended(true)
		defer listComposite.SetSuspended(false)
		for _, r := range todoRows {
			r.Dispose()
		}
		todoRows = todoRows[:0]

		for _, todo := range todoModel.GetFilteredTodos(menuModel.GetActiveTab()) {
			todo := todo
			row, err := newTodoRow(listComposite, todo, func(t *Todo) {
				todoModel.ChangeCompleted(t)
				refreshList()
			})
			if err == nil {
				todoRows = append(todoRows, row)
			}
		}
	}

	refreshTabs = func() {
		active := menuModel.GetActiveTab()
		for i, lbl := range tabLabels {
			if TabFilter(i) == active {
				lbl.SetFont(tabBoldFont)
			} else {
				lbl.SetFont(tabFont)
			}
		}
	}

	if err := (MainWindow{
		AssignTo: &mw,
		Title:    "ToDo",
		MinSize:  Size{Width: 800, Height: 600},
		MaxSize:  Size{Width: 800, Height: 600},
		Background: SolidColorBrush{Color: colorBG},
		Layout:   VBox{MarginsZero: true, SpacingZero: true},
		Children: []Widget{
			Composite{
				Background: SolidColorBrush{Color: colorBG},
				Layout: VBox{
					Margins: Margins{Top: 10, Bottom: 10, Left: 24, Right: 24},
					Spacing: 0,
				},
				Children: []Widget{
					// Title
					Label{
						Text:      "ToDo",
						Font:      Font{Family: "Segoe UI", PointSize: 14, Bold: true},
						TextColor: colorWhite,
						MinSize:   Size{Height: 28},
					},
					VSpacer{Size: 14},
					// Input
					LineEdit{
						AssignTo:   &inputEdit,
						CueBanner:  "Add Task",
						Background: SolidColorBrush{Color: colorInput},
						TextColor:  colorWhite,
						Font:       Font{Family: "Segoe UI", PointSize: 10},
						MinSize:    Size{Width: 430, Height: 35},
						MaxSize:    Size{Height: 35},
					},
					VSpacer{Size: 14},
					// Tabs (populated imperatively below)
					Composite{
						AssignTo:   &tabsComposite,
						Background: SolidColorBrush{Color: colorBG},
						Layout:     HBox{MarginsZero: true, SpacingZero: true},
					},
					VSpacer{Size: 3},
					// Todo list
					ScrollView{
						Background: SolidColorBrush{Color: colorBG},
						Layout:     VBox{MarginsZero: true, SpacingZero: true},
						Children: []Widget{
							Composite{
								AssignTo:   &listComposite,
								Background: SolidColorBrush{Color: colorBG},
								Layout:     VBox{MarginsZero: true, Spacing: 5},
							},
						},
					},
				},
			},
		},
	}.Create()); err != nil {
		panic(err)
	}

	// Build tab labels imperatively (need mouse handlers)
	for i, tab := range menuModel.GetTabList() {
		tab := tab
		i := i

		// Left spacer (8px padding)
		lSpacer, _ := walk.NewHSpacer(tabsComposite)
		lSpacer.SetMinMaxSize(walk.Size{Width: 8}, walk.Size{Width: 8, Height: 28})

		lbl, _ := walk.NewLabel(tabsComposite)
		lbl.SetText(tab.Label())
		lbl.SetFont(tabFont)
		lbl.SetTextColor(colorText)
		lbl.SetMinMaxSize(walk.Size{Height: 28}, walk.Size{Height: 28})
		lbl.MouseDown().Attach(func(x, y int, button walk.MouseButton) {
			if button == walk.LeftButton {
				menuModel.SetActiveTab(tab)
				refreshTabs()
				refreshList()
			}
		})
		tabLabels = append(tabLabels, lbl)

		// Right spacer (8px padding)
		rSpacer, _ := walk.NewHSpacer(tabsComposite)
		rSpacer.SetMinMaxSize(walk.Size{Width: 8}, walk.Size{Width: 8, Height: 28})
		_ = i
	}

	// Handle Enter key on input
	inputEdit.KeyDown().Attach(func(key walk.Key) {
		if key == walk.KeyReturn {
			task := strings.TrimSpace(inputEdit.Text())
			if task != "" {
				todoModel.AddTodo(task)
				inputEdit.SetText("")
				refreshList()
			}
		}
	})

	refreshTabs()
	refreshList()

	mw.Run()
}