"""Data models: Todo, TabFilter, TodoModel, MenuModel."""
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
    def __init__(self) -> None:
        self._list: List[Todo] = [
            Todo(1, "Task1", False),
            Todo(2, "Task2", True),
            Todo(3, "Task3", False),
            Todo(4, "Task4", False),
        ]
        self._next_id = 5

    def add_todo(self, task: str) -> None:
        self._list.append(Todo(self._next_id, task, False))
        self._next_id += 1

    def change_completed(self, todo_id: int) -> None:
        for todo in self._list:
            if todo.id == todo_id:
                todo.is_completed = not todo.is_completed
                break

    def get_filtered_todos(self, tab_filter: TabFilter) -> List[Todo]:
        if tab_filter == TabFilter.ACTIVE:
            return [t for t in self._list if not t.is_completed]
        if tab_filter == TabFilter.COMPLETED:
            return [t for t in self._list if t.is_completed]
        return list(self._list)


class MenuModel:
    def __init__(self) -> None:
        self._active_tab = TabFilter.ALL

    def get_active_tab(self) -> TabFilter:
        return self._active_tab

    def set_active_tab(self, tab: TabFilter) -> None:
        self._active_tab = tab