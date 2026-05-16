#pragma once
#include <dear-imgui/imgui.h>
#include "../data.h"
#include "../theme.h"

inline void render_input(TodoModel& model, char* buf, int buf_size) {
    float  avail = ImGui::GetContentRegionAvail().x;
    ImVec2 pos   = ImGui::GetCursorScreenPos();

    ImGui::PushStyleColor(ImGuiCol_Text, col4(1.f, 1.f, 1.f));
    ImGui::SetNextItemWidth(avail);
    bool enter = ImGui::InputText(
        "##input", buf, buf_size,
        ImGuiInputTextFlags_EnterReturnsTrue);
    ImGui::PopStyleColor();

    if (ImGui::IsItemFocused()) {
        ImVec2 mn = ImGui::GetItemRectMin();
        ImVec2 mx = ImGui::GetItemRectMax();
        ImGui::GetWindowDrawList()->AddRect(
            mn, mx, IM_COL32(0x5D, 0xC2, 0xAF, 255), 4.f, 0, 1.f);
    }

    if (buf[0] == '\0' && !ImGui::IsItemActive()) {
        float text_h = ImGui::GetTextLineHeight();
        ImGui::GetWindowDrawList()->AddText(
            {pos.x + 16.f, pos.y + (Theme::INPUT_H - text_h) * 0.5f},
            IM_COL32(0x9B, 0x9B, 0x9B, 255), "Add Task");
    }

    if (enter && buf[0] != '\0') {
        model.add_todo(buf);
        buf[0] = '\0';
        ImGui::SetKeyboardFocusHere(-1);
    }

    ImGui::Dummy({0.f, Theme::INPUT_MB});
}