package ui

import (
	"strings"

	"gioui.org/font"
	"gioui.org/layout"
	"gioui.org/op/clip"
	"gioui.org/op/paint"
	"gioui.org/unit"
	"gioui.org/widget"
	"gioui.org/widget/material"

	"github.com/webcyou-org/todo-gui/tree/main/Go/Gio/data"
	"github.com/webcyou-org/todo-gui/tree/main/Go/Gio/theme"
)

type AppState struct {
	TodoModel  *data.TodoModel
	MenuModel  *data.MenuModel
	Editor     widget.Editor
	TabClicks  [3]widget.Clickable
	TodoClicks map[int]*widget.Clickable
	List       layout.List
}

func NewAppState() *AppState {
	s := &AppState{
		TodoModel:  data.NewTodoModel(),
		MenuModel:  data.NewMenuModel(),
		TodoClicks: make(map[int]*widget.Clickable),
	}
	s.Editor.SingleLine = true
	s.Editor.Submit = true
	s.List.Axis = layout.Vertical
	return s
}

func (s *AppState) EnsureClick(id int) *widget.Clickable {
	if _, ok := s.TodoClicks[id]; !ok {
		s.TodoClicks[id] = new(widget.Clickable)
	}
	return s.TodoClicks[id]
}

func (s *AppState) Frame(gtx C, th *material.Theme) D {
	for {
		ev, ok := s.Editor.Update(gtx)
		if !ok {
			break
		}
		if _, ok := ev.(widget.SubmitEvent); ok {
			task := strings.TrimSpace(s.Editor.Text())
			if task != "" {
				s.TodoModel.AddTodo(task)
				s.Editor.SetText("")
			}
		}
	}

	for i := range s.TabClicks {
		if s.TabClicks[i].Clicked(gtx) {
			s.MenuModel.SetActiveTab(data.TabFilter(i))
		}
	}

	filtered := s.TodoModel.GetFilteredTodos(s.MenuModel.GetActiveTab())
	for _, todo := range filtered {
		if s.EnsureClick(todo.ID).Clicked(gtx) {
			s.TodoModel.ChangeCompleted(todo)
		}
	}

	defer clip.Rect{Max: gtx.Constraints.Max}.Push(gtx.Ops).Pop()
	paint.Fill(gtx.Ops, theme.ColorBG)

	return layout.Inset{
		Top: unit.Dp(10), Bottom: unit.Dp(10),
		Left: unit.Dp(24), Right: unit.Dp(24),
	}.Layout(gtx, func(gtx C) D {
		return layout.Flex{Axis: layout.Vertical}.Layout(gtx,
			layout.Rigid(func(gtx C) D {
				lbl := material.Label(th, unit.Sp(18), "ToDo")
				lbl.Color = theme.ColorWhite
				lbl.Font.Weight = font.Bold
				return lbl.Layout(gtx)
			}),
			layout.Rigid(layout.Spacer{Height: unit.Dp(14)}.Layout),
			layout.Rigid(func(gtx C) D {
				return LayoutInput(gtx, th, &s.Editor)
			}),
			layout.Rigid(layout.Spacer{Height: unit.Dp(14)}.Layout),
			layout.Rigid(func(gtx C) D {
				return LayoutTabs(gtx, th, s.MenuModel.GetTabList(), s.MenuModel.GetActiveTab(), s.TabClicks[:])
			}),
			layout.Rigid(layout.Spacer{Height: unit.Dp(3)}.Layout),
			layout.Flexed(1, func(gtx C) D {
				return LayoutList(gtx, th, &s.List, filtered, s.TodoClicks)
			}),
		)
	})
}