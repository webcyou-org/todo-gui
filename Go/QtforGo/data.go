package main

type TabFilter int

const (
	TabAll TabFilter = iota
	TabActive
	TabCompleted
)

type Todo struct {
	ID          int
	Task        string
	IsCompleted bool
}

type TodoModel struct {
	todos  []Todo
	nextID int
}

func newTodoModel() *TodoModel {
	m := &TodoModel{nextID: 1}
	m.addSample("Buy groceries", false)
	m.addSample("Walk the dog", true)
	m.addSample("Read a book", false)
	return m
}

func (m *TodoModel) AddTodo(task string) {
	m.todos = append(m.todos, Todo{ID: m.nextID, Task: task})
	m.nextID++
}

func (m *TodoModel) ToggleCompleted(id int) {
	for i := range m.todos {
		if m.todos[i].ID == id {
			m.todos[i].IsCompleted = !m.todos[i].IsCompleted
			return
		}
	}
}

func (m *TodoModel) FilteredTodos(tab TabFilter) []Todo {
	if tab == TabAll {
		result := make([]Todo, len(m.todos))
		copy(result, m.todos)
		return result
	}
	var result []Todo
	for _, t := range m.todos {
		if (tab == TabCompleted) == t.IsCompleted {
			result = append(result, t)
		}
	}
	return result
}

func (m *TodoModel) addSample(task string, completed bool) {
	m.todos = append(m.todos, Todo{ID: m.nextID, Task: task, IsCompleted: completed})
	m.nextID++
}

type MenuModel struct {
	ActiveTab TabFilter
}