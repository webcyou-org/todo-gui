#pragma once
#include <dear-imgui/imgui.h>
#include "../data.h"
#include "../theme.h"

inline void render_input(TodoModel& model, char* buf, int buf_size) {
    static bool s_refocus = false;

    float  avail   = ImGui::GetContentRegionAvail().x;
    float  font_h  = ImGui::GetTextLineHeight();
    // FramePadding.y that gives exactly INPUT_H total: (INPUT_H - font_h) / 2
    float  pad_y   = (Theme::INPUT_H - font_h) * 0.5f;
    ImVec2 pos     = ImGui::GetCursorScreenPos();

    // Re-focus the input on the frame after a task was submitted.
    if (s_refocus) { ImGui::SetKeyboardFocusHere(); s_refocus = false; }

    ImGui::PushStyleColor(ImGuiCol_Text, col4(1.f, 1.f, 1.f));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(16.f, pad_y));
    ImGui::SetNextItemWidth(avail);
    bool enter = ImGui::InputText(
        "##input", buf, buf_size,
        ImGuiInputTextFlags_EnterReturnsTrue);
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();

    if (ImGui::IsItemFocused()) {
        ImVec2 mn = ImGui::GetItemRectMin();
        ImVec2 mx = ImGui::GetItemRectMax();
        ImGui::GetWindowDrawList()->AddRect(
            mn, mx, IM_COL32(0x5D, 0xC2, 0xAF, 255), 4.f, 0, 1.f);
    }

    if (buf[0] == '\0' && !ImGui::IsItemActive()) {
        ImGui::GetWindowDrawList()->AddText(
            {pos.x + 16.f, pos.y + (Theme::INPUT_H - font_h) * 0.5f},
            IM_COL32(0x9B, 0x9B, 0x9B, 255), "Add Task");
    }

    if (enter && buf[0] != '\0') {
        model.add_todo(buf);
        buf[0] = '\0';
        s_refocus = true;  // re-focus on the next frame
    }

    ImGui::Dummy({0.f, Theme::INPUT_MB});
}