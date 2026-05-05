package main

import (
	"github.com/therecipe/qt/core"
	"github.com/therecipe/qt/gui"
	"github.com/therecipe/qt/widgets"
)

type TabMenu struct {
	Widget     *widgets.QWidget
	labels     map[TabFilter]*widgets.QLabel
	onTabClick func(TabFilter)
}

func newTabMenu(onTabClick func(TabFilter)) *TabMenu {
	tm := &TabMenu{
		labels:     make(map[TabFilter]*widgets.QLabel),
		onTabClick: onTabClick,
	}

	tm.Widget = widgets.NewQWidget(nil, core.Qt__Widget)
	layout := widgets.NewQHBoxLayout2(tm.Widget)
	layout.SetContentsMargins(0, 0, 0, 0)
	layout.SetSpacing(0)

	tabs := []struct {
		tab  TabFilter
		text string
	}{
		{TabAll, "All"},
		{TabActive, "Active"},
		{TabCompleted, "Completed"},
	}
	for _, item := range tabs {
		lbl := tm.makeLabel(item.text, item.tab)
		tm.labels[item.tab] = lbl
		layout.AddWidget(lbl, 0, 0)
	}
	layout.AddStretch(1)

	return tm
}

func (tm *TabMenu) makeLabel(text string, tab TabFilter) *widgets.QLabel {
	lbl := widgets.NewQLabel2(text, nil, core.Qt__Widget)

	font := gui.NewQFont()
	font.SetPixelSize(14)
	lbl.SetFont(font)

	pal := lbl.Palette()
	pal.SetColor2(gui.QPalette__WindowText, T.Text)
	lbl.SetPalette(pal)

	lbl.SetContentsMargins(8, 0, 8, 0)
	lbl.SetFixedHeight(28)
	lbl.SetCursor(gui.NewQCursor2(core.Qt__PointingHandCursor))

	lbl.ConnectMousePressEvent(func(event *gui.QMouseEvent) {
		tm.onTabClick(tab)
	})

	return lbl
}

func (tm *TabMenu) SetActive(tab TabFilter) {
	for t, lbl := range tm.labels {
		font := lbl.Font()
		font.SetBold(t == tab)
		lbl.SetFont(font)
	}
}