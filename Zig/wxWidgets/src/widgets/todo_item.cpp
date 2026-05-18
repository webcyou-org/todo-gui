#include "todo_item.h"

wxDEFINE_EVENT(EVT_TOGGLE_TODO, wxCommandEvent);

static const wxColour C_BG       { 0x1C, 0x1C, 0x1C };
static const wxColour C_SURFACE  { 0x2A, 0x2A, 0x2A };
static const wxColour C_TEXT     { 0xD2, 0xD2, 0xD2 };
static const wxColour C_WHITE    { 0xFF, 0xFF, 0xFF };
static const wxColour C_MUTED    { 0x9B, 0x9B, 0x9B };
static const wxColour C_ACCENT   { 0x5D, 0xC2, 0xAF };
static const wxColour C_CB_BORDER{ 0xD9, 0xD9, 0xD9 };

// Layout constants
static constexpr int CB_SIZE  = 16;
static constexpr int CB_PAD_L = 10;
static constexpr int CB_MR    = 18;
static constexpr int LABEL_X  = CB_PAD_L + CB_SIZE + CB_MR;  // = 44
static constexpr int ITEM_H   = 35;

// ── TodoItemWidget ─────────────────────────────────────────────────────────────

TodoItemWidget::TodoItemWidget(wxWindow* parent, const WxTodo& todo)
    : wxWindow(parent, wxID_ANY), m_todo(todo)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    SetMinSize(wxSize(-1, ITEM_H));
    SetMaxSize(wxSize(-1, ITEM_H));
    SetCursor(wxCURSOR_HAND);
    Bind(wxEVT_PAINT,   &TodoItemWidget::OnPaint, this);
    Bind(wxEVT_LEFT_UP, &TodoItemWidget::OnClick, this);
    Bind(wxEVT_SIZE,    [this](wxSizeEvent& e){ Refresh(); e.Skip(); });
}

wxRect TodoItemWidget::CbRect() const {
    int cbY = (ITEM_H - CB_SIZE) / 2;
    return wxRect(CB_PAD_L, cbY, CB_SIZE, CB_SIZE);
}

void TodoItemWidget::OnPaint(wxPaintEvent&) {
    wxAutoBufferedPaintDC dc(this);
    dc.SetBackground(wxBrush(C_BG));
    dc.Clear();

    auto* gc = wxGraphicsContext::Create(dc);
    if (!gc) return;

    wxRect r = GetClientRect();

    // Background rounded rect
    gc->SetBrush(wxBrush(C_SURFACE));
    gc->SetPen(wxPen(C_SURFACE, 0));
    gc->DrawRoundedRectangle(r.x, r.y, r.width, r.height, 4);

    // Checkbox
    wxRect cb = CbRect();
    bool done = (m_todo.is_completed != 0);
    if (done) {
        gc->SetBrush(*wxTRANSPARENT_BRUSH);
        gc->SetPen(wxPen(C_CB_BORDER, 1));
        gc->DrawEllipse(cb.x, cb.y, cb.width, cb.height);

        gc->SetPen(wxPen(C_ACCENT, 1.5));
        gc->SetBrush(*wxTRANSPARENT_BRUSH);
        double cx = cb.x + cb.width  / 2.0;
        double cy = cb.y + cb.height / 2.0;
        wxGraphicsPath path = gc->CreatePath();
        path.MoveToPoint(cx - 4, cy);
        path.AddLineToPoint(cx - 1, cy + 3);
        path.AddLineToPoint(cx + 4, cy - 3);
        gc->StrokePath(path);
    } else {
        gc->SetBrush(*wxTRANSPARENT_BRUSH);
        gc->SetPen(wxPen(C_CB_BORDER, 1));
        gc->DrawEllipse(cb.x, cb.y, cb.width, cb.height);
    }

    // Task label
    wxString label = wxString::FromUTF8(m_todo.task);
    wxFont font(wxFontInfo(wxSize(0, 14)));
    font.SetStrikethrough(done);
    gc->SetFont(font, done ? C_MUTED : C_TEXT);

    double tw, th;
    gc->GetTextExtent(label.ToStdWstring(), &tw, &th);
    gc->DrawText(label.ToStdWstring(),
                 static_cast<double>(LABEL_X),
                 (ITEM_H - th) / 2.0);

    delete gc;
}

void TodoItemWidget::OnClick(wxMouseEvent& e) {
    if (CbRect().Contains(e.GetPosition())) {
        wxCommandEvent evt(EVT_TOGGLE_TODO, GetId());
        evt.SetInt(static_cast<int>(m_todo.id));
        GetEventHandler()->ProcessEvent(evt);
    }
}

// ── TodoList ──────────────────────────────────────────────────────────────────

TodoList::TodoList(wxWindow* parent)
    : wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                       wxVSCROLL | wxBORDER_NONE)
{
    SetBackgroundColour(C_BG);
    SetScrollRate(0, 1);

    m_sizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(m_sizer);
}

void TodoList::Refresh(const std::vector<WxTodo>& todos) {
    m_sizer->Clear(true);
    for (const auto& t : todos) {
        auto* item = new TodoItemWidget(this, t);
        item->Bind(EVT_TOGGLE_TODO, [this](wxCommandEvent& e) {
            GetEventHandler()->ProcessEvent(e);
        });
        m_sizer->Add(item, 0, wxEXPAND | wxBOTTOM, 5);
    }
    m_sizer->AddStretchSpacer(1);
    FitInside();
    wxScrolledWindow::Refresh();
}