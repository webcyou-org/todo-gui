#include "todo_item.h"

wxDEFINE_EVENT(EVT_TOGGLE_TODO, wxCommandEvent);

// ── TodoItemWidget ────────────────────────────────────────────────────────────

TodoItemWidget::TodoItemWidget(wxWindow* parent, const Todo& todo)
    : wxWindow(parent, wxID_ANY), m_todo(todo)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    SetMinSize(wxSize(-1, Theme::ITEM_H));
    SetMaxSize(wxSize(-1, Theme::ITEM_H));
    SetCursor(wxCURSOR_HAND);
    Bind(wxEVT_PAINT,   &TodoItemWidget::OnPaint, this);
    Bind(wxEVT_LEFT_UP, &TodoItemWidget::OnClick, this);
    Bind(wxEVT_SIZE,    [this](wxSizeEvent& e){ Refresh(); e.Skip(); });
}

wxRect TodoItemWidget::CbRect() const {
    int cbY = (Theme::ITEM_H - Theme::CB_SIZE) / 2;
    return wxRect(Theme::CB_PAD_L, cbY, Theme::CB_SIZE, Theme::CB_SIZE);
}

void TodoItemWidget::OnPaint(wxPaintEvent&) {
    wxAutoBufferedPaintDC dc(this);
    dc.SetBackground(wxBrush(GetParent()->GetBackgroundColour()));
    dc.Clear();

    auto* gc = wxGraphicsContext::Create(dc);
    if (!gc) return;

    wxRect r = GetClientRect();

    gc->SetBrush(wxBrush(Theme::SURFACE));
    gc->SetPen(wxPen(Theme::SURFACE, 0));
    gc->DrawRoundedRectangle(r.x, r.y, r.width, r.height, 4);

    wxRect cb = CbRect();
    if (m_todo.isCompleted) {
        gc->SetBrush(wxBrush(Theme::ACCENT));
        gc->SetPen(wxPen(Theme::ACCENT, 0));
        gc->DrawEllipse(cb.x, cb.y, cb.width, cb.height);

        gc->SetPen(wxPen(Theme::WHITE, 1.5));
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
        gc->SetPen(wxPen(Theme::CB_BORDER, 1));
        gc->DrawEllipse(cb.x, cb.y, cb.width, cb.height);
    }

    wxFont font(wxFontInfo(wxSize(0, 14)));
    font.SetStrikethrough(m_todo.isCompleted);
    gc->SetFont(font, m_todo.isCompleted ? Theme::MUTED : Theme::TEXT);

    double textX = Theme::LABEL_X;
    double textH = Theme::ITEM_H;
    double tw, th;
    gc->GetTextExtent(m_todo.task.ToStdWstring(), &tw, &th);
    gc->DrawText(m_todo.task.ToStdWstring(), textX, (textH - th) / 2.0);

    delete gc;
}

void TodoItemWidget::OnClick(wxMouseEvent& e) {
    if (CbRect().Contains(e.GetPosition())) {
        wxCommandEvent evt(EVT_TOGGLE_TODO, GetId());
        evt.SetInt(m_todo.id);
        GetEventHandler()->ProcessEvent(evt);
    }
}

// ── TodoList ──────────────────────────────────────────────────────────────────

TodoList::TodoList(wxWindow* parent)
    : wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                       wxVSCROLL | wxBORDER_NONE)
{
    SetBackgroundColour(Theme::BG);
    SetScrollRate(0, 1);

    m_sizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(m_sizer);
}

void TodoList::Refresh(const std::vector<Todo>& todos) {
    m_sizer->Clear(true);
    for (const auto& t : todos) {
        auto* item = new TodoItemWidget(this, t);
        item->Bind(EVT_TOGGLE_TODO, [this](wxCommandEvent& e) {
            GetEventHandler()->ProcessEvent(e);
        });
        m_sizer->Add(item, 0, wxEXPAND | wxBOTTOM, Theme::ITEM_MB);
    }
    m_sizer->AddStretchSpacer(1);
    FitInside();
    wxScrolledWindow::Refresh();
}