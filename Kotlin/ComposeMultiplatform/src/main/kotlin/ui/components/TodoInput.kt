package ui.components

import androidx.compose.foundation.background
import androidx.compose.foundation.border
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.text.BasicTextField
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.focus.FocusRequester
import androidx.compose.ui.focus.focusRequester
import androidx.compose.ui.focus.onFocusChanged
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.SolidColor
import androidx.compose.ui.input.key.*
import androidx.compose.ui.text.TextStyle
import androidx.compose.foundation.layout.Box
import androidx.compose.material3.Text
import androidx.compose.ui.unit.dp
import ui.Theme

@Composable
fun TodoInput(onAddTodo: (String) -> Unit) {
    var text by remember { mutableStateOf("") }
    var isFocused by remember { mutableStateOf(false) }
    val focusRequester = remember { FocusRequester() }
    val shape = RoundedCornerShape(Theme.RADIUS)

    val borderColor = if (isFocused) Theme.ACCENT else Color.Transparent

    BasicTextField(
        value = text,
        onValueChange = { text = it },
        singleLine = true,
        textStyle = TextStyle(color = Theme.WHITE, fontSize = Theme.FONT_NORM),
        cursorBrush = SolidColor(Theme.ACCENT),
        modifier = Modifier
            .fillMaxWidth()
            .height(Theme.INPUT_H)
            .clip(shape)
            .background(Theme.INPUT)
            .border(1.dp, borderColor, shape)
            .focusRequester(focusRequester)
            .onFocusChanged { isFocused = it.isFocused }
            .onPreviewKeyEvent { event ->
                if (event.type == KeyEventType.KeyDown && event.key == Key.Enter) {
                    val trimmed = text.trim()
                    if (trimmed.isNotEmpty()) {
                        onAddTodo(trimmed)
                        text = ""
                    }
                    true
                } else false
            },
        decorationBox = { innerTextField ->
            Box(
                contentAlignment = Alignment.CenterStart,
                modifier = Modifier.padding(horizontal = Theme.INPUT_PX, vertical = Theme.INPUT_PY),
            ) {
                if (text.isEmpty()) {
                    Text(
                        text = "Add Task",
                        color = Theme.MUTED,
                        fontSize = Theme.FONT_NORM,
                    )
                }
                innerTextField()
            }
        },
    )

    LaunchedEffect(Unit) {
        focusRequester.requestFocus()
    }
}