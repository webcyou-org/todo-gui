package main

import "image"

func renderInput(rgba *image.RGBA, state *AppState, focused bool, x, y, w int) image.Rectangle {
	h := sc(35)
	rect := image.Rect(x, y, x+w, y+h)
	fillRect(rgba, rect, colInput)
	if focused {
		strokeRect(rgba, rect, colAccent)
	}
	baseline := vertCenter(faceNormal, y, h)
	if state.InputText == "" {
		drawTextAt(rgba, faceNormal, x+sc(16), baseline, colMuted, "Add Task")
	} else {
		drawTextAt(rgba, faceNormal, x+sc(16), baseline, colWhite, state.InputText)
	}
	return rect
}