import Foundation

class AppState: ObservableObject {
    @Published var todos: [Todo] = [
        Todo(id: 1, task: "Task 1", isCompleted: false),
        Todo(id: 2, task: "Task 2", isCompleted: true),
        Todo(id: 3, task: "Task 3", isCompleted: false),
        Todo(id: 4, task: "Task 4", isCompleted: false),
    ]
    @Published var activeFilter: TabFilter = .all
    private var nextId = 5

    var filteredTodos: [Todo] {
        switch activeFilter {
        case .all:       return todos
        case .active:    return todos.filter { !$0.isCompleted }
        case .completed: return todos.filter {  $0.isCompleted }
        }
    }

    func addTodo(_ task: String) {
        let trimmed = task.trimmingCharacters(in: .whitespaces)
        guard !trimmed.isEmpty else { return }
        todos.append(Todo(id: nextId, task: trimmed, isCompleted: false))
        nextId += 1
    }

    func toggleCompleted(id: Int) {
        guard let i = todos.firstIndex(where: { $0.id == id }) else { return }
        todos[i].isCompleted.toggle()
    }

    func removeData(id: Int) {
        todos.removeAll { $0.id == id }
    }
}