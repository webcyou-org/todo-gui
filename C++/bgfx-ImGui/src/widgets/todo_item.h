#pragma once
#include <cstdio>
#include <dear-imgui/imgui.h>
#include "../data.h"
#include "../theme.h"

static inline bool checkbox_circle(int id, bool completed) {
    ImDrawList* dl  = ImGui::GetWindowDrawList();
    ImVec2 p        = ImGui::GetCursorScreenPos();
    float  r        = Theme::CB_SIZE * 0.5f;
    ImVec2 center   = {p.x + r, p.y + r};

    if (completed) {
        dl->AddCircleFilled(center, r, IM_COL32(0x5D, 0xC2, 0xAF, 255));
        dl->AddLine({center.x - 4, center.y},     {center.x - 1, center.y + 3},
                    IM_COL32(255, 255, 255, 255), 1.5f);
        dl->AddLine({center.x - 1, center.y + 3}, {center.x + 4, center.y - 3},
                    IM_COL32(255, 255, 255, 255), 1.5f);
    } else {
        dl->AddCircle(center, r - 1.f, IM_COL32(0xD9, 0xD9, 0xD9, 255), 0, 2.f);
    }

    char label[32];
    snprintf(label, sizeof(label), "##cb%d", id);
    ImGui::InvisibleButton(label, {Theme::CB_SIZE, Theme::CB_SIZE});
    bool clicked = ImGui::IsItemClicked();
    ImGui::SameLine(0.f, Theme::CB_MR);
    return clicked;
}

static inline void strikethrough_text(const char* text, bool strike, ImVec4 color) {
    ImVec2 pos = ImGui::GetCursorScreenPos();
    ImGui::PushStyleColor(ImGuiCol_Text, color);
    ImGui::TextUnformatted(text);
    ImGui::PopStyleColor();
    if (strike) {
        ImVec2 end = ImGui::GetItemRectMax();
        float  mid = (pos.y + end.y) * 0.5f;
        ImGui::GetWindowDrawList()->AddLine(
            {pos.x, mid}, {end.x, mid},
            ImGui::ColorConvertFloat4ToU32(color), 1.f);
    }
}

inline void render_todo_list(TodoModel& model, TabFilter tab) {
    float avail_h = ImGui::GetContentRegionAvail().y;
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, {0.f, Theme::ITEM_MB});
    ImGui::BeginChild("##list", {0.f, avail_h}, false, ImGuiWindowFlags_None);

    auto  todos   = model.filtered(tab);
    float avail_w = ImGui::GetContentRegionAvail().x;
    float text_h  = ImGui::GetTextLineHeight();

    for (auto& todo : todos) {
        ImVec2 item_pos = ImGui::GetCursorScreenPos();

        ImGui::GetWindowDrawList()->AddRectFilled(
            item_pos, {item_pos.x + avail_w, item_pos.y + Theme::ITEM_H},
            IM_COL32(0x2A, 0x2A, 0x2A, 255), 4.f);

        ImGui::SetCursorScreenPos(
            {item_pos.x + 10.f,
             item_pos.y + (Theme::ITEM_H - Theme::CB_SIZE) * 0.5f});

        if (checkbox_circle(todo.id, todo.is_completed))
            model.toggle(todo.id);

        ImGui::SetCursorScreenPos(
            {ImGui::GetCursorScreenPos().x,
             item_pos.y + (Theme::ITEM_H - text_h) * 0.5f});

        ImVec4 txt_col = todo.is_completed
            ? col4(Theme::MUTED_R, Theme::MUTED_G, Theme::MUTED_B)
            : col4(Theme::TEXT_R,  Theme::TEXT_G,  Theme::TEXT_B);

        strikethrough_text(todo.task.c_str(), todo.is_completed, txt_col);

        ImGui::SetCursorScreenPos({item_pos.x, item_pos.y + Theme::ITEM_H});
        ImGui::Dummy({avail_w, 0.f});
    }

    ImGui::EndChild();
    ImGui::PopStyleVar();
}