package ui

import androidx.compose.foundation.background
import androidx.compose.foundation.layout.*
import androidx.compose.material3.Text
import androidx.compose.runtime.*
import androidx.compose.ui.Modifier
import androidx.compose.ui.text.font.FontWeight
import data.TabFilter
import data.Todo
import data.initialTodos
import ui.components.TabMenu
import ui.components.TodoInput
import ui.components.TodoList

@Composable
fun App() {
    var todos by remember { mutableStateOf(initialTodos()) }
    var nextId by remember { mutableStateOf(initialTodos().size + 1) }
    var activeTab by remember { mutableStateOf(TabFilter.All) }

    Box(
        modifier = Modifier
            .fillMaxSize()
            .background(Theme.BG)
            .padding(horizontal = Theme.PAD_H, vertical = Theme.PAD_V)
    ) {
        Column(modifier = Modifier.fillMaxSize()) {
            // Title
            Text(
                text = "ToDo",
                color = Theme.WHITE,
                fontSize = Theme.FONT_TITLE,
                fontWeight = FontWeight.Bold,
            )
            Spacer(modifier = Modifier.height(Theme.TITLE_MB))

            // Input
            TodoInput(onAddTodo = { task ->
                todos = todos + Todo(id = nextId++, task = task)
            })
            Spacer(modifier = Modifier.height(Theme.INPUT_MB))

            // Tab menu
            TabMenu(activeTab = activeTab, onTabSelected = { activeTab = it })
            Spacer(modifier = Modifier.height(Theme.TAB_MB))

            // Todo list
            TodoList(
                todos = todos,
                activeTab = activeTab,
                onToggle = { id ->
                    todos = todos.map { if (it.id == id) it.copy(isCompleted = !it.isCompleted) else it }
                },
            )
        }
    }
}