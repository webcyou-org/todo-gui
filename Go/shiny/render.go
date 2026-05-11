package main

import "image"

func render(rgba *image.RGBA, state *AppState, inputFocused bool) {
	regions = nil

	bounds := rgba.Bounds()
	W := bounds.Max.X
	padX := sc(24)
	padY := sc(10)
	contentW := W - padX*2
	y := padY

	// Background
	fillRect(rgba, bounds, colBG)

	// Title
	boldM := faceBold18.Metrics()
	titleBaseline := y + boldM.Ascent.Ceil()
	drawTextAt(rgba, faceBold18, padX, titleBaseline, colWhite, "ToDo")
	y += boldM.Ascent.Ceil() + boldM.Descent.Ceil() + sc(14)

	// Input
	inputRect = renderInput(rgba, state, inputFocused, padX, y, contentW)
	y += sc(35) + sc(14)

	// Tabs
	renderTabs(rgba, state, padX, y)
	y += sc(28) + sc(3)

	// Todo list
	renderTodoList(rgba, state, padX, y, contentW)
}