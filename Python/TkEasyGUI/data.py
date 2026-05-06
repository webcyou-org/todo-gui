"""Data model."""
from enum import Enum
from dataclasses import dataclass
from typing import List


class TabFilter(Enum):
    ALL       = "all"
    ACTIVE    = "active"
    COMPLETED = "completed"


@dataclass
class Todo:
    id: int
    task: str
    is_completed: bool = False


class TodoModel:
    def __init__(self):
        self._todos: List[Todo] = [
            Todo(1, "Task1"),
            Todo(2, "Task2", True),
            Todo(3, "Task3"),
            Todo(4, "Task4"),
        ]
        self._next_id = 5

    def add(self, task: str):
        self._todos.append(Todo(self._next_id, task))
        self._next_id += 1

    def toggle(self, id: int):
        for t in self._todos:
            if t.id == id:
                t.is_completed = not t.is_completed
                return

    def filtered(self, f: TabFilter) -> List[Todo]:
        if f == TabFilter.ALL:
            return list(self._todos)
        return [t for t in self._todos if t.is_completed == (f == TabFilter.COMPLETED)]


class MenuModel:
    def __init__(self):
        self.active_tab = TabFilter.ALL