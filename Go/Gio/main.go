package main

import (
	"log"
	"os"

	"gioui.org/app"
	"gioui.org/font/gofont"
	"gioui.org/op"
	"gioui.org/text"
	"gioui.org/unit"
	"gioui.org/widget/material"

	"github.com/webcyou-org/todo-gui/tree/main/Go/Gio/ui"
)

func main() {
	go func() {
		w := new(app.Window)
		w.Option(app.Title("ToDo"), app.Size(unit.Dp(800), unit.Dp(600)))
		if err := run(w); err != nil {
			log.Fatal(err)
		}
		os.Exit(0)
	}()
	app.Main()
}

func run(w *app.Window) error {
	th := material.NewTheme()
	th.Shaper = text.NewShaper(text.WithCollection(gofont.Collection()))

	state := ui.NewAppState()

	var ops op.Ops
	for {
		switch e := w.Event().(type) {
		case app.DestroyEvent:
			return e.Err
		case app.FrameEvent:
			gtx := app.NewContext(&ops, e)
			state.Frame(gtx, th)
			e.Frame(gtx.Ops)
		}
	}
}