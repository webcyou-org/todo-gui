package main

// TabFilter represents the active tab selection.
type TabFilter int

const (
	TabAll       TabFilter = 0
	TabActive    TabFilter = 1
	TabCompleted TabFilter = 2
)

func (t TabFilter) Label() string {
	switch t {
	case TabAll:
		return "All"
	case TabActive:
		return "Active"
	case TabCompleted:
		return "Completed"
	}
	return ""
}

// Todo is a single task item.
type Todo struct {
	ID          int
	Task        string
	IsCompleted bool
}

// TodoModel manages the todo list.
type TodoModel struct {
	todos  []*Todo
	nextID int
}

func NewTodoModel() *TodoModel {
	m := &TodoModel{nextID: 1}
	m.AddTodo("Task 1")
	t2 := m.AddTodo("Task 2")
	t2.IsCompleted = true
	m.AddTodo("Task 3")
	m.AddTodo("Task 4")
	return m
}

func (m *TodoModel) AddTodo(task string) *Todo {
	t := &Todo{ID: m.nextID, Task: task}
	m.nextID++
	m.todos = append(m.todos, t)
	return t
}

func (m *TodoModel) ChangeCompleted(t *Todo) {
	t.IsCompleted = !t.IsCompleted
}

func (m *TodoModel) GetFilteredTodos(tab TabFilter) []*Todo {
	var result []*Todo
	for _, t := range m.todos {
		switch tab {
		case TabAll:
			result = append(result, t)
		case TabActive:
			if !t.IsCompleted {
				result = append(result, t)
			}
		case TabCompleted:
			if t.IsCompleted {
				result = append(result, t)
			}
		}
	}
	return result
}

// MenuModel manages the tab state.
type MenuModel struct {
	activeTab TabFilter
	tabs      []TabFilter
}

func NewMenuModel() *MenuModel {
	return &MenuModel{
		activeTab: TabAll,
		tabs:      []TabFilter{TabAll, TabActive, TabCompleted},
	}
}

func (m *MenuModel) GetActiveTab() TabFilter    { return m.activeTab }
func (m *MenuModel) SetActiveTab(t TabFilter)   { m.activeTab = t }
func (m *MenuModel) GetTabList() []TabFilter    { return m.tabs }