package ui

import (
	"gioui.org/font"
	"gioui.org/layout"
	"gioui.org/unit"
	"gioui.org/widget"
	"gioui.org/widget/material"

	"github.com/webcyou-org/todo-gui/tree/main/Go/Gio/data"
	"github.com/webcyou-org/todo-gui/tree/main/Go/Gio/theme"
)

func LayoutTabs(gtx C, th *material.Theme, tabs []data.TabFilter, active data.TabFilter, clicks []widget.Clickable) D {
	children := make([]layout.FlexChild, 0, len(tabs))
	for i, tab := range tabs {
		i, tab := i, tab
		isActive := tab == active
		children = append(children, layout.Rigid(func(gtx C) D {
			return clicks[i].Layout(gtx, func(gtx C) D {
				return layout.Inset{Left: unit.Dp(8), Right: unit.Dp(8)}.Layout(gtx, func(gtx C) D {
					lbl := material.Label(th, unit.Sp(14), tab.Label())
					lbl.Color = theme.ColorText
					if isActive {
						lbl.Font.Weight = font.Bold
					}
					return lbl.Layout(gtx)
				})
			})
		}))
	}
	return layout.Flex{Axis: layout.Horizontal}.Layout(gtx, children...)
}