#include "tab_menu.h"
#include "theme.h"

static const TabFilter kTabValues[] = {
    TabFilter::All, TabFilter::Active, TabFilter::Completed
};

void render_tab_menu(MenuModel& menu, ImFont* font_bold_14) {
    // Transparent button style, 8px h-pad, 28px line-height
    float tab_pad_y = (Theme::TAB_H - Theme::FONT_NORMAL) * 0.5f;
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.f);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,    {Theme::TAB_PX, tab_pad_y});
    ImGui::PushStyleColor(ImGuiCol_Button,        Theme::C_TRANS);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, Theme::C_TRANS);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive,  Theme::C_TRANS);
    ImGui::PushStyleColor(ImGuiCol_Text,          Theme::C_TEXT);

    for (int i = 0; i < 3; i++) {
        bool active = (menu.activeTab() == kTabValues[i]);
        if (active && font_bold_14) ImGui::PushFont(font_bold_14);

        ImGui::PushID(i);
        if (ImGui::Button(MenuModel::label(kTabValues[i])))
            menu.setActiveTab(kTabValues[i]);
        ImGui::PopID();

        if (active && font_bold_14) ImGui::PopFont();
        if (i < 2) ImGui::SameLine(0.f, 0.f);
    }

    ImGui::PopStyleColor(4);
    ImGui::PopStyleVar(2);
}