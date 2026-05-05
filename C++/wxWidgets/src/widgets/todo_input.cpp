#include "todo_input.h"

TodoInput::TodoInput(wxWindow* parent, wxWindowID id)
    : wxWindow(parent, id)
{
    SetBackgroundColour(Theme::INPUT);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    SetMinSize(wxSize(-1, Theme::INPUT_H));
    SetMaxSize(wxSize(-1, Theme::INPUT_H));

    m_text = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition,
                            wxDefaultSize, wxTE_PROCESS_ENTER | wxBORDER_NONE);
    m_text->SetBackgroundColour(Theme::INPUT);
    m_text->SetForegroundColour(Theme::WHITE);
    m_text->SetHint("Add Task");
    m_text->SetFont(wxFont(wxFontInfo(wxSize(0, 14))));

    auto* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(m_text, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 16);
    SetSizer(sizer);

    m_text->Bind(wxEVT_SET_FOCUS,  &TodoInput::OnChildFocus, this);
    m_text->Bind(wxEVT_KILL_FOCUS, &TodoInput::OnChildBlur,  this);
    Bind(wxEVT_PAINT, &TodoInput::OnPaint, this);
    Bind(wxEVT_SIZE,  &TodoInput::OnSize,  this);
}

void TodoInput::OnChildFocus(wxFocusEvent& e) { m_focused = true;  Refresh(); e.Skip(); }
void TodoInput::OnChildBlur (wxFocusEvent& e) { m_focused = false; Refresh(); e.Skip(); }
void TodoInput::OnSize      (wxSizeEvent&  e) { Refresh(); e.Skip(); }

void TodoInput::OnPaint(wxPaintEvent&) {
    wxAutoBufferedPaintDC dc(this);
    dc.SetBackground(wxBrush(GetParent()->GetBackgroundColour()));
    dc.Clear();

    auto* gc = wxGraphicsContext::Create(dc);
    if (!gc) return;

    wxRect r = GetClientRect();
    gc->SetBrush(wxBrush(Theme::INPUT));
    gc->SetPen(m_focused ? wxPen(Theme::ACCENT, 1) : wxPen(Theme::INPUT, 1));
    gc->DrawRoundedRectangle(r.x, r.y, r.width, r.height, 4);

    delete gc;
}