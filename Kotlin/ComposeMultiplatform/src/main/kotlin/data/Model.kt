package data

data class Todo(
    val id: Int,
    val task: String,
    val isCompleted: Boolean = false,
)

enum class TabFilter {
    All, Active, Completed;

    val label: String get() = name
}

fun initialTodos(): List<Todo> = listOf(
    Todo(1, "Task 1"),
    Todo(2, "Task 2", isCompleted = true),
    Todo(3, "Task 3"),
    Todo(4, "Task 4"),
)
