package main

import (
	"image"
	"time"
)

func renderInput(rgba *image.RGBA, state *AppState, focused bool, x, y, w int) image.Rectangle {
	h := sc(35)
	rect := image.Rect(x, y, x+w, y+h)
	fillRect(rgba, rect, colInput)
	if focused {
		strokeRect(rgba, rect, colAccent)
	}
	baseline := vertCenter(faceNormal, y, h)
	textX := x + sc(16)
	if state.InputText == "" && !focused {
		drawTextAt(rgba, faceNormal, textX, baseline, colMuted, "Add Task")
	} else if state.InputText != "" {
		drawTextAt(rgba, faceNormal, textX, baseline, colWhite, state.InputText)
	}

	// Draw blinking text cursor when focused.
	if focused {
		cursorX := textX + measureText(faceNormal, state.InputText)
		// Blink at ~1 Hz: show cursor during the first 500 ms of each second.
		blink := (time.Now().UnixMilli() / 500) % 2
		if blink == 0 {
			m := faceNormal.Metrics()
			cursorTop := baseline - m.Ascent.Ceil()
			cursorBot := baseline + m.Descent.Ceil()
			fillRect(rgba, image.Rect(cursorX, cursorTop, cursorX+sc(2), cursorBot), colWhite)
		}
	}
	return rect
}