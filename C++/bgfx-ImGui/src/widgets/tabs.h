#pragma once
#include <dear-imgui/imgui.h>
#include "../data.h"
#include "../theme.h"

inline void render_tabs(TabFilter& current_tab) {
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{4.f, 0.f});

    struct Tab { const char* label; TabFilter filter; };
    const Tab tabs[] = {
        {"All",       TabFilter::All},
        {"Active",    TabFilter::Active},
        {"Completed", TabFilter::Completed},
    };

    for (const auto& tab : tabs) {
        bool   active    = (current_tab == tab.filter);
        ImVec2 text_size = ImGui::CalcTextSize(tab.label);
        float  btn_w     = text_size.x + 2.f * Theme::TAB_PX + (active ? 1.f : 0.f);
        float  btn_h     = Theme::TAB_LINE_H;
        ImVec2 pos       = ImGui::GetCursorScreenPos();

        ImGui::InvisibleButton(tab.label, {btn_w, btn_h});
        if (ImGui::IsItemClicked()) current_tab = tab.filter;

        if (ImGui::IsItemHovered())
            ImGui::GetWindowDrawList()->AddRectFilled(
                pos, {pos.x + btn_w, pos.y + btn_h}, IM_COL32(255, 255, 255, 13));

        float    tx      = pos.x + Theme::TAB_PX;
        float    ty      = pos.y + (btn_h - text_size.y) * 0.5f;
        uint32_t txt_col = IM_COL32(0xD2, 0xD2, 0xD2, 255);

        ImGui::GetWindowDrawList()->AddText({tx, ty}, txt_col, tab.label);
        if (active)
            ImGui::GetWindowDrawList()->AddText({tx + 0.4f, ty}, txt_col, tab.label);

        ImGui::SameLine(0, 0);
    }

    ImGui::NewLine();
    ImGui::PopStyleVar();
    ImGui::Dummy({0.f, Theme::TABS_MB});
}