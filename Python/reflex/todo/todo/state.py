"""Application state."""
import reflex as rx
from typing import List


class Todo(rx.Base):
    id: int
    task: str
    is_completed: bool = False


class TodoState(rx.State):
    todos: List[Todo] = [
        Todo(id=1, task="Task1"),
        Todo(id=2, task="Task2", is_completed=True),
        Todo(id=3, task="Task3"),
        Todo(id=4, task="Task4"),
    ]
    active_tab: str = "all"
    next_id: int = 5

    @rx.var
    def filtered_todos(self) -> List[Todo]:
        if self.active_tab == "active":
            return [t for t in self.todos if not t.is_completed]
        if self.active_tab == "completed":
            return [t for t in self.todos if t.is_completed]
        return self.todos

    def handle_submit(self, form_data: dict):
        task = form_data.get("new_task", "").strip()
        if task:
            self.todos.append(Todo(id=self.next_id, task=task))
            self.next_id += 1

    def toggle_todo(self, todo_id: int):
        for todo in self.todos:
            if todo.id == todo_id:
                todo.is_completed = not todo.is_completed
                break

    def set_tab(self, tab: str):
        self.active_tab = tab