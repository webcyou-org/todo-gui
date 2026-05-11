package main

import "github.com/mattn/go-gtk/gdk"

// Design tokens — single source of truth for all colors, sizes, and fonts.
const (
	C_BG        = "#1C1C1C"
	C_SURFACE   = "#2A2A2A"
	C_INPUT     = "#303030"
	C_TEXT      = "#D2D2D2"
	C_WHITE     = "#FFFFFF"
	C_MUTED     = "#9B9B9B"
	C_ACCENT    = "#5DC2AF"
	C_CB_BORDER = "#D9D9D9"
)

func color(hex string) *gdk.Color {
	return gdk.NewColor(hex)
}