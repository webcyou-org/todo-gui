package main

import (
	"embed"
	"log"
	"net"
	"net/http"

	"github.com/zserge/lorca"
	"todo/model"
)

//go:embed frontend
var assets embed.FS

func main() {
	todoModel := model.NewTodoModel()
	menuModel := model.NewMenuModel()

	ln, err := net.Listen("tcp", "127.0.0.1:0")
	if err != nil {
		log.Fatal(err)
	}
	defer ln.Close()

	go http.Serve(ln, http.FileServer(http.FS(assets))) //nolint

	addr := "http://" + ln.Addr().String() + "/frontend/index.html"

	ui, err := lorca.New("", "", 800, 600, "--remote-allow-origins=*")
	if err != nil {
		log.Fatal(err)
	}
	defer ui.Close()

	// Bind Go model functions to JavaScript
	ui.Bind("goAddTodo", func(task string) {
		todoModel.AddTodo(task)
	})

	ui.Bind("goToggleTodo", func(id int) {
		todoModel.ChangeCompleted(id)
	})

	ui.Bind("goSetActiveTab", func(text string) {
		menuModel.SetActiveTab(text)
	})

	ui.Bind("goGetTodos", func() []model.Todo {
		active := menuModel.GetActiveTab()
		return todoModel.GetFilteredTodos(active.Text)
	})

	ui.Bind("goGetTabs", func() []model.TabMenu {
		return menuModel.GetTabList()
	})

	ui.Load(addr)
	<-ui.Done()
}