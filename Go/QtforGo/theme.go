package main

import "github.com/therecipe/qt/gui"

type themeColors struct {
	BG, Surface, Input, Text, White, Muted, Accent, CBBorder *gui.QColor
}

var T *themeColors

func initTheme() {
	T = &themeColors{
		BG:       gui.NewQColor3(0x1C, 0x1C, 0x1C, 255),
		Surface:  gui.NewQColor3(0x2A, 0x2A, 0x2A, 255),
		Input:    gui.NewQColor3(0x30, 0x30, 0x30, 255),
		Text:     gui.NewQColor3(0xD2, 0xD2, 0xD2, 255),
		White:    gui.NewQColor3(0xFF, 0xFF, 0xFF, 255),
		Muted:    gui.NewQColor3(0x9B, 0x9B, 0x9B, 255),
		Accent:   gui.NewQColor3(0x5D, 0xC2, 0xAF, 255),
		CBBorder: gui.NewQColor3(0xD9, 0xD9, 0xD9, 255),
	}
}

const (
	contentH = 24
	contentV = 10
	inputH   = 35
	itemH    = 35
	itemMB   = 5
	cbSize   = 16
	cbPadL   = 10
	cbMR     = 18
	labelX   = cbPadL + cbSize + cbMR // = 44
)