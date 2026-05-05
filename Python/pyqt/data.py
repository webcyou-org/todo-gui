from enum import Enum, auto
from dataclasses import dataclass


class TabFilter(Enum):
    ALL = auto()
    ACTIVE = auto()
    COMPLETED = auto()


@dataclass
class Todo:
    id: int
    task: str
    is_completed: bool = False


class TodoModel:
    def __init__(self):
        self._todos: list[Todo] = []
        self._next_id = 1
        self._add_sample("Buy groceries")
        self._add_sample("Walk the dog", completed=True)
        self._add_sample("Read a book")

    def add_todo(self, task: str):
        self._todos.append(Todo(id=self._next_id, task=task))
        self._next_id += 1

    def toggle_completed(self, todo_id: int):
        for todo in self._todos:
            if todo.id == todo_id:
                todo.is_completed = not todo.is_completed
                return

    def filtered_todos(self, tab: TabFilter) -> list[Todo]:
        if tab == TabFilter.ALL:
            return list(self._todos)
        return [t for t in self._todos
                if (tab == TabFilter.COMPLETED) == t.is_completed]

    def _add_sample(self, task: str, completed: bool = False):
        self._todos.append(Todo(id=self._next_id, task=task, is_completed=completed))
        self._next_id += 1


class MenuModel:
    def __init__(self):
        self.active_tab = TabFilter.ALL