#include "tab_menu.h"

wxDEFINE_EVENT(EVT_TAB_CHANGED, wxCommandEvent);

TabMenu::TabMenu(wxWindow* parent, wxWindowID id)
    : wxWindow(parent, id)
{
    SetBackgroundColour(Theme::BG);
    SetMinSize(wxSize(-1, 28));
    SetMaxSize(wxSize(-1, 28));

    auto* sizer = new wxBoxSizer(wxHORIZONTAL);
    SetSizer(sizer);

    for (auto [filter, label] : std::initializer_list<std::pair<TabFilter, const char*>>{
            {TabFilter::All, "All"},
            {TabFilter::Active, "Active"},
            {TabFilter::Completed, "Completed"}})
    {
        auto* lbl = new wxStaticText(this, wxID_ANY, label,
                                      wxDefaultPosition, wxDefaultSize);
        lbl->SetForegroundColour(Theme::TEXT);
        lbl->SetBackgroundColour(Theme::BG);
        lbl->SetFont(wxFont(wxFontInfo(wxSize(0, 14))));
        lbl->SetCursor(wxCURSOR_HAND);

        sizer->AddSpacer(8);
        sizer->Add(lbl, 0, wxALIGN_CENTER_VERTICAL);
        sizer->AddSpacer(8);

        m_labels[filter] = lbl;

        lbl->Bind(wxEVT_LEFT_UP, [this, filter](wxMouseEvent&) {
            OnTabClick(filter);
        });
    }
    sizer->AddStretchSpacer(1);

    SetActive(TabFilter::All);
}

void TabMenu::SetActive(TabFilter tab) {
    m_active = tab;
    for (auto& [f, lbl] : m_labels) {
        wxFont font = lbl->GetFont();
        font.SetWeight(f == tab ? wxFONTWEIGHT_BOLD : wxFONTWEIGHT_NORMAL);
        lbl->SetFont(font);
    }
    Refresh();
}

void TabMenu::OnTabClick(TabFilter tab) {
    wxCommandEvent evt(EVT_TAB_CHANGED, GetId());
    evt.SetInt(static_cast<int>(tab));
    GetEventHandler()->ProcessEvent(evt);
}