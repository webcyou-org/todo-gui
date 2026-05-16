#pragma once
#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include "../wx_bridge.h"

class TodoInput : public wxWindow {
public:
    TodoInput(wxWindow* parent, wxWindowID id = wxID_ANY);
    wxTextCtrl* GetTextCtrl() const { return m_text; }

private:
    wxTextCtrl* m_text    = nullptr;
    bool        m_focused = false;

    void OnChildFocus(wxFocusEvent& e);
    void OnChildBlur (wxFocusEvent& e);
    void OnPaint     (wxPaintEvent& e);
    void OnSize      (wxSizeEvent&  e);
};