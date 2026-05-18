package ui.components

import androidx.compose.foundation.Canvas
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.interaction.MutableInteractionSource
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.remember
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.graphics.drawscope.Stroke
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.style.TextDecoration
import androidx.compose.ui.unit.dp
import data.TabFilter
import data.Todo
import ui.Theme

@Composable
fun TodoList(
    todos: List<Todo>,
    activeTab: TabFilter,
    onToggle: (Int) -> Unit,
) {
    val filtered = when (activeTab) {
        TabFilter.All       -> todos
        TabFilter.Active    -> todos.filter { !it.isCompleted }
        TabFilter.Completed -> todos.filter { it.isCompleted }
    }

    LazyColumn(
        modifier = Modifier.fillMaxSize(),
        verticalArrangement = Arrangement.spacedBy(Theme.ITEM_MB),
    ) {
        items(filtered, key = { it.id }) { todo ->
            TodoItem(todo = todo, onToggle = { onToggle(todo.id) })
        }
    }
}

@Composable
private fun TodoItem(todo: Todo, onToggle: () -> Unit) {
    Row(
        verticalAlignment = Alignment.CenterVertically,
        modifier = Modifier
            .fillMaxWidth()
            .height(Theme.ITEM_H)
            .clip(RoundedCornerShape(Theme.RADIUS))
            .background(Theme.SURFACE)
            .padding(Theme.ITEM_PAD),
    ) {
        // Circular checkbox
        Canvas(
            modifier = Modifier
                .size(Theme.CB_SIZE)
                .clickable(
                    indication = null,
                    interactionSource = remember { MutableInteractionSource() },
                    onClick = onToggle,
                ),
        ) {
            val r = size.minDimension / 2f
            val center = Offset(r, r)
            if (todo.isCompleted) {
                drawCircle(
                    color = Theme.CB_BORDER,
                    radius = r - 1.dp.toPx(),
                    style = Stroke(width = 2.dp.toPx()),
                )
                // Checkmark in accent color
                val sw = 1.5.dp.toPx()
                drawLine(
                    color = Theme.ACCENT,
                    start = Offset(center.x - r * 0.45f, center.y),
                    end   = Offset(center.x - r * 0.1f,  center.y + r * 0.45f),
                    strokeWidth = sw,
                )
                drawLine(
                    color = Theme.ACCENT,
                    start = Offset(center.x - r * 0.1f, center.y + r * 0.45f),
                    end   = Offset(center.x + r * 0.5f, center.y - r * 0.4f),
                    strokeWidth = sw,
                )
            } else {
                drawCircle(
                    color = Theme.CB_BORDER,
                    radius = r - 1.dp.toPx(),
                    style = Stroke(width = 2.dp.toPx()),
                )
            }
        }

        Spacer(modifier = Modifier.width(Theme.CB_MR))

        Text(
            text = todo.task,
            color = if (todo.isCompleted) Theme.MUTED else Theme.TEXT,
            fontSize = Theme.FONT_NORM,
            style = TextStyle(
                textDecoration = if (todo.isCompleted) TextDecoration.LineThrough else TextDecoration.None,
                fontSize = Theme.FONT_NORM,
                color = if (todo.isCompleted) Theme.MUTED else Theme.TEXT,
            ),
        )
    }
}