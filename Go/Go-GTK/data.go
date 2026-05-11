package main

// TabFilter represents the active tab filter.
type TabFilter string

const (
	TabAll       TabFilter = "All"
	TabActive    TabFilter = "Active"
	TabCompleted TabFilter = "Completed"
)

// Todo is a single task item.
type Todo struct {
	ID          int
	Task        string
	IsCompleted bool
}

// TodoModel manages the todo list and business logic.
type TodoModel struct {
	list   []Todo
	nextID int
}

// NewTodoModel creates a TodoModel seeded with default tasks.
func NewTodoModel() *TodoModel {
	m := &TodoModel{nextID: 1}
	defaults := []struct {
		task string
		done bool
	}{
		{"Task 1", false},
		{"Task 2", true},
		{"Task 3", false},
		{"Task 4", false},
	}
	for _, d := range defaults {
		m.list = append(m.list, Todo{ID: m.nextID, Task: d.task, IsCompleted: d.done})
		m.nextID++
	}
	return m
}

func (m *TodoModel) AddTodo(task string) {
	m.list = append(m.list, Todo{ID: m.nextID, Task: task, IsCompleted: false})
	m.nextID++
}

func (m *TodoModel) GetData() []Todo {
	result := make([]Todo, len(m.list))
	copy(result, m.list)
	return result
}

func (m *TodoModel) FindByID(id int) *Todo {
	for i := range m.list {
		if m.list[i].ID == id {
			return &m.list[i]
		}
	}
	return nil
}

func (m *TodoModel) ChangeCompleted(id int) {
	if t := m.FindByID(id); t != nil {
		t.IsCompleted = !t.IsCompleted
	}
}

func (m *TodoModel) GetFilteredTodos(tab TabFilter) []Todo {
	var result []Todo
	for _, t := range m.list {
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

func (m *TodoModel) RemoveData(id int) {
	for i, t := range m.list {
		if t.ID == id {
			m.list = append(m.list[:i], m.list[i+1:]...)
			return
		}
	}
}

// MenuModel manages tab selection state.
type MenuModel struct {
	tabList   []TabFilter
	activeTab TabFilter
}

func NewMenuModel() *MenuModel {
	return &MenuModel{
		tabList:   []TabFilter{TabAll, TabActive, TabCompleted},
		activeTab: TabAll,
	}
}

func (m *MenuModel) SetActiveTab(tab TabFilter) { m.activeTab = tab }
func (m *MenuModel) GetActiveTab() TabFilter    { return m.activeTab }
func (m *MenuModel) GetTabList() []TabFilter    { return m.tabList }