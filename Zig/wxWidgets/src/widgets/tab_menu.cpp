#include "tab_menu.h"

wxDEFINE_EVENT(EVT_TAB_CHANGED, wxCommandEvent);

static const wxColour C_BG  { 0x1C, 0x1C, 0x1C };
static const wxColour C_TEXT{ 0xD2, 0xD2, 0xD2 };

TabMenu::TabMenu(wxWindow* parent, wxWindowID id)
    : wxWindow(parent, id)
{
    SetBackgroundColour(C_BG);
    SetMinSize(wxSize(-1, 28));
    SetMaxSize(wxSize(-1, 28));

    auto* sizer = new wxBoxSizer(wxHORIZONTAL);
    SetSizer(sizer);

    static const struct { WxTabFilter filter; const char* label; } tabs[] = {
        { WX_TAB_ALL,       "All"       },
        { WX_TAB_ACTIVE,    "Active"    },
        { WX_TAB_COMPLETED, "Completed" },
    };

    for (const auto& t : tabs) {
        auto* lbl = new wxStaticText(this, wxID_ANY, t.label,
                                     wxDefaultPosition, wxDefaultSize);
        lbl->SetForegroundColour(C_TEXT);
        lbl->SetBackgroundColour(C_BG);
        lbl->SetFont(wxFont(wxFontInfo(wxSize(0, 14))));
        lbl->SetCursor(wxCURSOR_HAND);

        sizer->AddSpacer(8);
        sizer->Add(lbl, 0, wxALIGN_CENTER_VERTICAL);
        sizer->AddSpacer(8);

        m_labels[t.filter] = lbl;

        WxTabFilter f = t.filter;
        lbl->Bind(wxEVT_LEFT_UP, [this, f](wxMouseEvent&) {
            OnTabClick(f);
        });
    }
    sizer->AddStretchSpacer(1);

    SetActive(WX_TAB_ALL);
}

void TabMenu::SetActive(WxTabFilter tab) {
    m_active = tab;
    for (auto& [f, lbl] : m_labels) {
        wxFont font = lbl->GetFont();
        font.SetWeight(f == tab ? wxFONTWEIGHT_BOLD : wxFONTWEIGHT_NORMAL);
        lbl->SetFont(font);
    }
    Refresh();
}

void TabMenu::OnTabClick(WxTabFilter tab) {
    wxCommandEvent evt(EVT_TAB_CHANGED, GetId());
    evt.SetInt(static_cast<int>(tab));
    GetEventHandler()->ProcessEvent(evt);
}