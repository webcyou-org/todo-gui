#pragma once
#include <wx/wx.h>
#include <map>
#include "../data.h"
#include "../theme.h"

wxDECLARE_EVENT(EVT_TAB_CHANGED, wxCommandEvent);

class TabMenu : public wxWindow {
public:
    TabMenu(wxWindow* parent, wxWindowID id = wxID_ANY);
    void SetActive(TabFilter tab);

private:
    std::map<TabFilter, wxStaticText*> m_labels;
    TabFilter                          m_active = TabFilter::All;

    void OnTabClick(TabFilter tab);
};