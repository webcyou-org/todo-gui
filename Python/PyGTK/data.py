from enum import Enum
from dataclasses import dataclass
from typing import List


class TabFilter(Enum):
    ALL = 0
    ACTIVE = 1
    COMPLETED = 2


@dataclass
class Todo:
    id: int
    task: str
    is_completed: bool = False


class TodoModel:
    def __init__(self):
        self._todos: List[Todo] = []
        self._next_id = 1
        self._sample("Task1")
        self._sample("Task2", True)
        self._sample("Task3")
        self._sample("Task4")

    def _sample(self, task: str, completed: bool = False):
        self._todos.append(Todo(self._next_id, task, completed))
        self._next_id += 1

    def add_todo(self, task: str):
        self._todos.append(Todo(self._next_id, task, False))
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