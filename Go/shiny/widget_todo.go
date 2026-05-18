package main

import "image"

func renderTodoList(rgba *image.RGBA, state *AppState, x, y, w int) {
	todos := state.FilteredTodos()
	itemH := sc(35)
	itemPad := sc(10)
	cbR := sc(8)    // checkbox radius: 16px logical → 8px radius
	cbGap := sc(18) // margin-right between checkbox and text

	for i, todo := range todos {
		itemRect := image.Rect(x, y, x+w, y+itemH)
		fillRect(rgba, itemRect, colSurface)

		// Circular checkbox (16px logical diameter)
		cbCX := x + itemPad + cbR
		cbCY := y + itemH/2
		if todo.IsCompleted {
			strokeCircle(rgba, cbCX, cbCY, cbR, max(1, sc(2)), colCBBorder)
			drawCheckmark(rgba, cbCX, cbCY, colAccent)
		} else {
			strokeCircle(rgba, cbCX, cbCY, cbR, max(1, sc(2)), colCBBorder)
		}

		// Task text: item-padding + checkbox(16px) + margin-right(18px)
		textX := x + itemPad + sc(16) + cbGap
		baseline := vertCenter(faceNormal, y, itemH)
		textCol := colText
		if todo.IsCompleted {
			textCol = colMuted
		}
		endX := drawTextAt(rgba, faceNormal, textX, baseline, textCol, todo.Task)

		// Strikethrough
		if todo.IsCompleted {
			m := faceNormal.Metrics()
			strikeY := baseline - m.Ascent.Ceil()/3
			fillRect(rgba, image.Rect(textX, strikeY, endX, strikeY+max(1, sc(1))), textCol)
		}

		// Checkbox click region
		todoID := todo.ID
		cbRect := image.Rect(x+itemPad, cbCY-cbR, x+itemPad+cbR*2, cbCY+cbR)
		regions = append(regions, region{cbRect, func() {
			state.ToggleCompleted(todoID)
		}})

		y += itemH
		if i < len(todos)-1 {
			y += sc(5)
		}
	}
}