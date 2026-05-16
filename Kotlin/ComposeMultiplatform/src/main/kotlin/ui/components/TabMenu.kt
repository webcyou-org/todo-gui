package ui.components

import androidx.compose.foundation.layout.*
import androidx.compose.foundation.clickable
import androidx.compose.foundation.interaction.MutableInteractionSource
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.remember
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.text.font.FontWeight
import data.TabFilter
import ui.Theme

@Composable
fun TabMenu(activeTab: TabFilter, onTabSelected: (TabFilter) -> Unit) {
    Row {
        TabFilter.entries.forEach { tab ->
            val isActive = tab == activeTab
            Box(
                contentAlignment = Alignment.Center,
                modifier = Modifier
                    .height(Theme.TAB_H)
                    .padding(horizontal = Theme.TAB_PX)
                    .clickable(
                        indication = null,
                        interactionSource = remember { MutableInteractionSource() },
                    ) { onTabSelected(tab) },
            ) {
                Text(
                    text = tab.label,
                    color = Theme.TEXT,
                    fontSize = Theme.FONT_NORM,
                    fontWeight = if (isActive) FontWeight.Bold else FontWeight.Normal,
                )
            }
        }
    }
}