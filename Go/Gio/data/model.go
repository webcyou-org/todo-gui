package data

type TabFilter int

const (
	All TabFilter = iota
	Active
	Completed
)

func (t TabFilter) Label() string {
	return [...]string{"All", "Active", "Completed"}[t]
}

type Todo struct {
	ID          int
	Task        string
	IsCompleted bool
}

type TodoModel struct {
	list   []*Todo
	nextID int
}

func NewTodoModel() *TodoModel {
	return &TodoModel{
		nextID: 5,
		list: []*Todo{
			{ID: 1, Task: "Task 1", IsCompleted: false},
			{ID: 2, Task: "Task 2", IsCompleted: true},
			{ID: 3, Task: "Task 3", IsCompleted: false},
			{ID: 4, Task: "Task 4", IsCompleted: false},
		},
	}
}

func (m *TodoModel) GetData() []*Todo { return m.list }

func (m *TodoModel) AddTodo(task string) {
	m.list = append(m.list, &Todo{ID: m.nextID, Task: task})
	m.nextID++
}

func (m *TodoModel) FindByID(id int) *Todo {
	for _, t := range m.list {
		if t.ID == id {
			return t
		}
	}
	return nil
}

func (m *TodoModel) ChangeCompleted(todo *Todo) {
	if t := m.FindByID(todo.ID); t != nil {
		t.IsCompleted = !t.IsCompleted
	}
}

func (m *TodoModel) GetFilteredTodos(tab TabFilter) []*Todo {
	var result []*Todo
	for _, t := range m.list {
		switch tab {
		case All:
			result = append(result, t)
		case Active:
			if !t.IsCompleted {
				result = append(result, t)
			}
		case Completed:
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

type MenuModel struct {
	tabs   []TabFilter
	active TabFilter
}

func NewMenuModel() *MenuModel {
	return &MenuModel{
		tabs:   []TabFilter{All, Active, Completed},
		active: All,
	}
}

func (m *MenuModel) SetActiveTab(tab TabFilter) { m.active = tab }
func (m *MenuModel) GetActiveTab() TabFilter    { return m.active }
func (m *MenuModel) GetTabList() []TabFilter    { return m.tabs }