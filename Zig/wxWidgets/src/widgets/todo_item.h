#pragma once
#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include <wx/scrolwin.h>
#include <vector>
#include "../wx_bridge.h"

wxDECLARE_EVENT(EVT_TOGGLE_TODO, wxCommandEvent);

class TodoItemWidget : public wxWindow {
public:
    TodoItemWidget(wxWindow* parent, const WxTodo& todo);

private:
    WxTodo m_todo;

    wxRect CbRect() const;
    void OnPaint(wxPaintEvent&);
    void OnClick(wxMouseEvent& e);
};

class TodoList : public wxScrolledWindow {
public:
    explicit TodoList(wxWindow* parent);
    void Refresh(const std::vector<WxTodo>& todos);

private:
    wxBoxSizer* m_sizer = nullptr;
};