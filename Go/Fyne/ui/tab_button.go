package ui

import (
	"fyne.io/fyne/v2"
	"fyne.io/fyne/v2/canvas"
	"fyne.io/fyne/v2/container"
	"fyne.io/fyne/v2/layout"
	"fyne.io/fyne/v2/widget"

	"github.com/webcyou-org/todo-gui/tree/main/Go/Fyne/apptheme"
	"github.com/webcyou-org/todo-gui/tree/main/Go/Fyne/data"
)

type TabButton struct {
	widget.BaseWidget
	tab    data.TabFilter
	active bool
	onTap  func(data.TabFilter)
}

func NewTabButton(tab data.TabFilter, active bool, onTap func(data.TabFilter)) *TabButton {
	b := &TabButton{tab: tab, active: active, onTap: onTap}
	b.ExtendBaseWidget(b)
	return b
}

func (b *TabButton) CreateRenderer() fyne.WidgetRenderer {
	text := canvas.NewText(b.tab.Label(), apptheme.ColorText)
	text.TextSize = 14
	text.TextStyle = fyne.TextStyle{Bold: b.active}
	return widget.NewSimpleRenderer(
		container.New(layout.NewCustomPaddedLayout(0, 0, 8, 8), text),
	)
}

func (b *TabButton) Tapped(_ *fyne.PointEvent) { b.onTap(b.tab) }
