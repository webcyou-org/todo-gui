#include "todo_input.h"

static const wxColour C_BG    { 0x1C, 0x1C, 0x1C };
static const wxColour C_INPUT { 0x30, 0x30, 0x30 };
static const wxColour C_WHITE { 0xFF, 0xFF, 0xFF };
static const wxColour C_ACCENT{ 0x5D, 0xC2, 0xAF };

TodoInput::TodoInput(wxWindow* parent, wxWindowID id)
    : wxWindow(parent, id)
{
    SetBackgroundColour(C_INPUT);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    SetMinSize(wxSize(-1, 35));
    SetMaxSize(wxSize(-1, 35));

    m_text = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition,
                            wxDefaultSize, wxTE_PROCESS_ENTER | wxBORDER_NONE);
    m_text->SetBackgroundColour(C_INPUT);
    m_text->SetForegroundColour(C_WHITE);
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
    dc.SetBackground(wxBrush(C_BG));
    dc.Clear();

    auto* gc = wxGraphicsContext::Create(dc);
    if (!gc) return;

    wxRect r = GetClientRect();
    gc->SetBrush(wxBrush(C_INPUT));
    gc->SetPen(m_focused ? wxPen(C_ACCENT, 1) : wxPen(C_INPUT, 1));
    gc->DrawRoundedRectangle(r.x, r.y, r.width, r.height, 4);

    delete gc;
}