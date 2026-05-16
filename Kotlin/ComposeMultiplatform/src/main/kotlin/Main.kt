import androidx.compose.ui.window.application
import androidx.compose.ui.window.Window
import androidx.compose.ui.window.rememberWindowState
import androidx.compose.ui.unit.DpSize
import androidx.compose.ui.unit.dp
import ui.App

fun main() = application {
    Window(
        onCloseRequest = ::exitApplication,
        title = "ToDo",
        state = rememberWindowState(size = DpSize(800.dp, 600.dp)),
        resizable = false,
    ) {
        App()
    }
}