#include "todo_list.h"
#include "theme.h"
#include <string>

void render_todo_list(TodoModel& model, TabFilter active_tab) {
    auto todos = model.filteredTodos(active_tab);

    // Scrollable child – transparent bg, full remaining space
    ImGui::PushStyleColor(ImGuiCol_ChildBg, Theme::C_TRANS);
    ImGui::BeginChild("##list", {0.f, 0.f}, false, ImGuiWindowFlags_None);
    ImGui::PopStyleColor();

    ImDrawList* dl = ImGui::GetWindowDrawList();

    for (const auto& todo : todos) {
        ImVec2 origin  = ImGui::GetCursorScreenPos();
        float  avail_w = ImGui::GetContentRegionAvail().x;
        float  item_h  = Theme::ITEM_H;
        float  pad     = 10.f;

        // ── Background ───────────────────────────────────────────────────────
        dl->AddRectFilled(
            origin,
            {origin.x + avail_w, origin.y + item_h},
            Theme::u32(Theme::C_SURFACE),
            Theme::ITEM_RADIUS);

        // ── Checkbox ─────────────────────────────────────────────────────────
        float  cb_y  = origin.y + (item_h - Theme::CB_SIZE) * 0.5f;
        ImVec2 cb_c  = {origin.x + pad + Theme::CB_SIZE * 0.5f,
                        cb_y + Theme::CB_SIZE * 0.5f};

        if (todo.is_completed) {
            dl->AddCircle(cb_c, Theme::CB_RADIUS,
                          Theme::u32(Theme::C_CB_BORDER), 32, 2.f);
            // Checkmark (two-segment line) in accent color
            float r = Theme::CB_RADIUS;
            dl->AddLine({cb_c.x - r * 0.45f, cb_c.y},
                        {cb_c.x - r * 0.1f,  cb_c.y + r * 0.45f},
                        Theme::u32(Theme::C_ACCENT), 1.5f);
            dl->AddLine({cb_c.x - r * 0.1f, cb_c.y + r * 0.45f},
                        {cb_c.x + r * 0.5f, cb_c.y - r * 0.4f},
                        Theme::u32(Theme::C_ACCENT), 1.5f);
        } else {
            dl->AddCircle(cb_c, Theme::CB_RADIUS,
                          Theme::u32(Theme::C_CB_BORDER), 32, 2.f);
        }

        // Invisible button for checkbox click
        ImGui::SetCursorScreenPos({origin.x + pad, cb_y});
        ImGui::InvisibleButton(("##cb" + std::to_string(todo.id)).c_str(),
                               {Theme::CB_SIZE, Theme::CB_SIZE});
        if (ImGui::IsItemClicked())
            model.toggleCompleted(todo.id);

        // ── Task text ─────────────────────────────────────────────────────────
        float text_x = origin.x + pad + Theme::CB_SIZE + Theme::CB_MR;
        float text_h = ImGui::GetTextLineHeight();
        float text_y = origin.y + (item_h - text_h) * 0.5f;
        ImU32 text_col = todo.is_completed
                       ? Theme::u32(Theme::C_MUTED)
                       : Theme::u32(Theme::C_TEXT);

        dl->AddText(ImGui::GetFont(), ImGui::GetFontSize(),
                    {text_x, text_y}, text_col, todo.task.c_str());

        // Strikethrough for completed tasks
        if (todo.is_completed) {
            float tw = ImGui::CalcTextSize(todo.task.c_str()).x;
            float ly = text_y + text_h * 0.55f;
            dl->AddLine({text_x, ly}, {text_x + tw, ly},
                        Theme::u32(Theme::C_MUTED), 1.f);
        }

        // Advance cursor to next item position (item_h + margin-bottom)
        ImGui::SetCursorScreenPos({origin.x, origin.y + item_h + Theme::ITEM_MB});
    }

    ImGui::EndChild();
}