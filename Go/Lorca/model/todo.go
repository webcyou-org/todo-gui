package model

import "sync"

type TabFilter string

const (
	TabAll       TabFilter = "All"
	TabActive    TabFilter = "Active"
	TabCompleted TabFilter = "Completed"
)

type Todo struct {
	ID          int    `json:"id"`
	Task        string `json:"task"`
	IsCompleted bool   `json:"isCompleted"`
}

type TabMenu struct {
	Text     TabFilter `json:"text"`
	IsActive bool      `json:"isActive"`
}

type TodoModel struct {
	mu     sync.Mutex
	list   []Todo
	nextID int
}

func NewTodoModel() *TodoModel {
	m := &TodoModel{nextID: 1}
	m.insertTodo("Task1", false)
	m.insertTodo("Task2", true)
	m.insertTodo("Task3", false)
	m.insertTodo("Task4", false)
	return m
}

func (m *TodoModel) insertTodo(task string, completed bool) {
	m.list = append(m.list, Todo{ID: m.nextID, Task: task, IsCompleted: completed})
	m.nextID++
}

func (m *TodoModel) AddTodo(task string) {
	if task == "" {
		return
	}
	m.mu.Lock()
	defer m.mu.Unlock()
	m.insertTodo(task, false)
}

func (m *TodoModel) GetData() []Todo {
	m.mu.Lock()
	defer m.mu.Unlock()
	result := make([]Todo, len(m.list))
	copy(result, m.list)
	return result
}

func (m *TodoModel) ChangeCompleted(id int) {
	m.mu.Lock()
	defer m.mu.Unlock()
	for i := range m.list {
		if m.list[i].ID == id {
			m.list[i].IsCompleted = !m.list[i].IsCompleted
			break
		}
	}
}

func (m *TodoModel) GetFilteredTodos(tab TabFilter) []Todo {
	m.mu.Lock()
	defer m.mu.Unlock()
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
	if result == nil {
		result = []Todo{}
	}
	return result
}

func (m *TodoModel) RemoveData(id int) {
	m.mu.Lock()
	defer m.mu.Unlock()
	for i, t := range m.list {
		if t.ID == id {
			m.list = append(m.list[:i], m.list[i+1:]...)
			break
		}
	}
}

type MenuModel struct {
	mu      sync.Mutex
	tabList []TabMenu
	active  int
}

func NewMenuModel() *MenuModel {
	return &MenuModel{
		tabList: []TabMenu{
			{Text: TabAll, IsActive: true},
			{Text: TabActive, IsActive: false},
			{Text: TabCompleted, IsActive: false},
		},
		active: 0,
	}
}

func (m *MenuModel) GetTabList() []TabMenu {
	m.mu.Lock()
	defer m.mu.Unlock()
	result := make([]TabMenu, len(m.tabList))
	copy(result, m.tabList)
	return result
}

func (m *MenuModel) GetActiveTab() TabMenu {
	m.mu.Lock()
	defer m.mu.Unlock()
	return m.tabList[m.active]
}

func (m *MenuModel) SetActiveTab(text string) {
	m.mu.Lock()
	defer m.mu.Unlock()
	for i := range m.tabList {
		m.tabList[i].IsActive = string(m.tabList[i].Text) == text
		if m.tabList[i].IsActive {
			m.active = i
		}
	}
}