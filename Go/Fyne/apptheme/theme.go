package apptheme

import (
	"image/color"

	"fyne.io/fyne/v2"
	ft "fyne.io/fyne/v2/theme"
)

// Design tokens
var (
	ColorBG       = color.NRGBA{R: 0x1C, G: 0x1C, B: 0x1C, A: 0xFF}
	ColorSurface  = color.NRGBA{R: 0x2A, G: 0x2A, B: 0x2A, A: 0xFF}
	ColorInput    = color.NRGBA{R: 0x30, G: 0x30, B: 0x30, A: 0xFF}
	ColorText     = color.NRGBA{R: 0xD2, G: 0xD2, B: 0xD2, A: 0xFF}
	ColorMuted    = color.NRGBA{R: 0x9B, G: 0x9B, B: 0x9B, A: 0xFF}
	ColorAccent   = color.NRGBA{R: 0x5D, G: 0xC2, B: 0xAF, A: 0xFF}
	ColorWhite    = color.NRGBA{R: 0xFF, G: 0xFF, B: 0xFF, A: 0xFF}
	ColorCBBorder = color.NRGBA{R: 0xD9, G: 0xD9, B: 0xD9, A: 0xFF}
)

// AppTheme implements fyne.Theme
type AppTheme struct{}

func (t *AppTheme) Color(name fyne.ThemeColorName, _ fyne.ThemeVariant) color.Color {
	switch name {
	case ft.ColorNameBackground:
		return ColorBG
	case ft.ColorNameForeground:
		return ColorText
	case ft.ColorNamePrimary:
		return ColorAccent
	case ft.ColorNameInputBackground:
		return ColorInput
	case ft.ColorNamePlaceHolder:
		return ColorMuted
	case ft.ColorNameHover:
		return ColorSurface
	case ft.ColorNameButton:
		return ColorSurface
	case ft.ColorNameSelection:
		return ColorAccent
	case ft.ColorNameScrollBar:
		return ColorSurface
	case ft.ColorNameShadow:
		return color.NRGBA{A: 0x40}
	}
	return ft.DefaultTheme().Color(name, ft.VariantDark)
}

func (t *AppTheme) Font(style fyne.TextStyle) fyne.Resource {
	return ft.DefaultTheme().Font(style)
}

func (t *AppTheme) Icon(name fyne.ThemeIconName) fyne.Resource {
	return ft.DefaultTheme().Icon(name)
}

func (t *AppTheme) Size(name fyne.ThemeSizeName) float32 {
	switch name {
	case ft.SizeNameText:
		return 14
	case ft.SizeNameInnerPadding:
		return 8
	case ft.SizeNamePadding:
		return 4
	}
	return ft.DefaultTheme().Size(name)
}