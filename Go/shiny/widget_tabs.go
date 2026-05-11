package main

import "image"

func renderTabs(rgba *image.RGBA, state *AppState, x, y int) {
	tabLabels := []string{"All", "Active", "Completed"}
	tabFilters := []TabFilter{TabAll, TabActive, TabCompleted}
	tabH := sc(28)
	padH := sc(8) // horizontal padding each side
	baseline := vertCenter(faceNormal, y, tabH)
	curX := x
	for i, label := range tabLabels {
		isActive := state.ActiveTab == tabFilters[i]
		face := faceNormal
		if isActive {
			face = faceBold14
		}
		// Use normal-weight width for stable tab spacing
		tw := measureText(faceNormal, label)
		tabBounds := image.Rect(curX, y, curX+tw+padH*2, y+tabH)
		drawTextAt(rgba, face, curX+padH, baseline, colText, label)
		idx := i
		bounds := tabBounds
		regions = append(regions, region{bounds, func() {
			state.ActiveTab = tabFilters[idx]
		}})
		curX += tw + padH*2
	}
}