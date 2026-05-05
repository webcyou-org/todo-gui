package main

import (
	"fmt"

	"github.com/therecipe/qt/gui"
	"github.com/therecipe/qt/widgets"
)

func newTodoInput() *widgets.QLineEdit {
	input := widgets.NewQLineEdit(nil)
	input.SetFixedHeight(inputH)
	input.SetPlaceholderText("Add Task")
	input.SetStyleSheet(fmt.Sprintf(`
		QLineEdit {
			background: %s;
			color: %s;
			border: 1px solid transparent;
			border-radius: 4px;
			padding: 4px 16px;
		}
		QLineEdit:focus {
			border: 1px solid %s;
		}
	`, T.Input.Name(), T.White.Name(), T.Accent.Name()))

	pal := input.Palette()
	pal.SetColor2(gui.QPalette__PlaceholderText, T.Muted)
	input.SetPalette(pal)

	return input
}