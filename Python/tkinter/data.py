from dataclasses import dataclass
from enum import Enum
from typing import List


class TabFilter(Enum):
    ALL       = "All"
    ACTIVE    = "Active"
    COMPLETED = "Completed"


@dataclass
class Todo:
    id: int
    task: str
    is_completed: bool = False


class TodoModel:
    def __init__(self):
        self._todos: List[Todo] = [
            Todo(1, "Task 1", False),
            Todo(2, "Task 2", True),
            Todo(3, "Task 3", False),
            Todo(4, "Task 4", False),
        ]
        self._next_id = 5

    def get_data(self) -> List[Todo]:
        return list(self._todos)

    def add_todo(self, task: str) -> None:
        task = task.strip()
        if not task:
            return
        self._todos.append(Todo(self._next_id, task, False))
        self._next_id += 1

    def find_by_id(self, id: int):
        return next((t for t in self._todos if t.id == id), None)

    def change_completed(self, todo: Todo) -> None:
        if t := self.find_by_id(todo.id):
            t.is_completed = not t.is_completed

    def get_filtered_todos(self, tab: TabFilter) -> List[Todo]:
        if tab == TabFilter.ALL:
            return list(self._todos)
        elif tab == TabFilter.ACTIVE:
            return [t for t in self._todos if not t.is_completed]
        else:
            return [t for t in self._todos if t.is_completed]

    def remove_data(self, id: int) -> None:
        self._todos = [t for t in self._todos if t.id != id]


class MenuModel:
    TABS = [TabFilter.ALL, TabFilter.ACTIVE, TabFilter.COMPLETED]

    def __init__(self):
        self._active_tab = TabFilter.ALL

    def set_active_tab(self, tab: TabFilter) -> None:
        self._active_tab = tab

    def get_active_tab(self) -> TabFilter:
        return self._active_tab

    def get_tab_list(self) -> List[TabFilter]:
        return list(self.TABS)