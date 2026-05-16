package ui

import androidx.compose.ui.graphics.Color
import androidx.compose.ui.unit.Dp
import androidx.compose.ui.unit.TextUnit
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp

object Theme {
    val BG       = Color(0xFF1C1C1C)
    val SURFACE  = Color(0xFF2A2A2A)
    val INPUT    = Color(0xFF303030)
    val TEXT     = Color(0xFFD2D2D2)
    val WHITE    = Color(0xFFFFFFFF)
    val MUTED    = Color(0xFF9B9B9B)
    val ACCENT   = Color(0xFF5DC2AF)
    val CB_BORDER = Color(0xFFD9D9D9)

    val PAD_H: Dp = 24.dp
    val PAD_V: Dp = 10.dp

    val TITLE_MB: Dp = 14.dp
    val INPUT_MB: Dp = 14.dp
    val TAB_MB:   Dp = 3.dp
    val ITEM_MB:  Dp = 5.dp

    val INPUT_H:  Dp = 35.dp
    val ITEM_H:   Dp = 35.dp
    val INPUT_PX: Dp = 16.dp
    val INPUT_PY: Dp = 4.dp
    val TAB_PX:   Dp = 8.dp
    val TAB_H:    Dp = 28.dp
    val ITEM_PAD: Dp = 10.dp
    val CB_SIZE:  Dp = 16.dp
    val CB_MR:    Dp = 18.dp
    val RADIUS:   Dp = 4.dp
    val CB_RADIUS: Dp = 8.dp

    val FONT_TITLE: TextUnit = 18.sp
    val FONT_NORM:  TextUnit = 14.sp
}