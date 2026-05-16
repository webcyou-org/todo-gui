#pragma once
#include <wx/wx.h>
#include <map>
#include "../wx_bridge.h"

wxDECLARE_EVENT(EVT_TAB_CHANGED, wxCommandEvent);

class TabMenu : public wxWindow {
public:
    TabMenu(wxWindow* parent, wxWindowID id = wxID_ANY);
    void SetActive(WxTabFilter tab);

private:
    WxTabFilter                        m_active = WX_TAB_ALL;
    std::map<WxTabFilter, wxStaticText*> m_labels;

    void OnTabClick(WxTabFilter tab);
};