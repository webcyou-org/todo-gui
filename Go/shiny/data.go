package main

type Todo struct {
	ID          int
	Task        string
	IsCompleted bool
}

type TabFilter int

const (
	TabAll TabFilter = iota
	TabActive
	TabCompleted
)

type AppState struct {
	Todos     []Todo
	ActiveTab TabFilter
	InputText string
	nextID    int
}

func NewAppState() *AppState {
	return &AppState{
		Todos: []Todo{
			{ID: 1, Task: "Task1", IsCompleted: false},
			{ID: 2, Task: "Task2", IsCompleted: true},
			{ID: 3, Task: "Task3", IsCompleted: false},
			{ID: 4, Task: "Task4", IsCompleted: false},
		},
		ActiveTab: TabAll,
		nextID:    5,
	}
}

func (a *AppState) AddTodo(task string) {
	if task == "" {
		return
	}
	a.Todos = append(a.Todos, Todo{
		ID:          a.nextID,
		Task:        task,
		IsCompleted: false,
	})
	a.nextID++
}

func (a *AppState) ToggleCompleted(id int) {
	for i := range a.Todos {
		if a.Todos[i].ID == id {
			a.Todos[i].IsCompleted = !a.Todos[i].IsCompleted
			return
		}
	}
}

func (a *AppState) FilteredTodos() []Todo {
	switch a.ActiveTab {
	case TabActive:
		var result []Todo
		for _, t := range a.Todos {
			if !t.IsCompleted {
				result = append(result, t)
			}
		}
		return result
	case TabCompleted:
		var result []Todo
		for _, t := range a.Todos {
			if t.IsCompleted {
				result = append(result, t)
			}
		}
		return result
	default:
		return a.Todos
	}
}