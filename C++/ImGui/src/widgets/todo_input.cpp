#include "todo_input.h"
#include "theme.h"
#include <cstring>

void render_todo_input(TodoModel& model, char* buf, int buf_size,
                       bool& needs_focus, ImFont* /*font_bold_14*/) {
    ImDrawList* dl = ImGui::GetWindowDrawList();

    // Frame style: bg=#303030, no built-in border, height=35px, radius=4px
    float frame_pad_y = (Theme::INPUT_H - Theme::FONT_NORMAL) * 0.5f - 1.f;
    ImGui::PushStyleColor(ImGuiCol_FrameBg,        Theme::C_INPUT);
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, Theme::C_INPUT);
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive,  Theme::C_INPUT);
    ImGui::PushStyleColor(ImGuiCol_Text,           Theme::C_WHITE);
    ImGui::PushStyleColor(ImGuiCol_TextDisabled,   Theme::C_MUTED);   // placeholder
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding,   Theme::ITEM_RADIUS);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,    {16.f, frame_pad_y});
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.f);

    if (needs_focus) {
        ImGui::SetKeyboardFocusHere(0);
        needs_focus = false;
    }

    ImGui::SetNextItemWidth(-FLT_MIN);   // full content width
    bool enter = ImGui::InputTextWithHint(
        "##input", "Add Task", buf, buf_size,
        ImGuiInputTextFlags_EnterReturnsTrue);

    // Focus border drawn on top of the widget
    if (ImGui::IsItemFocused()) {
        auto p0 = ImGui::GetItemRectMin();
        auto p1 = ImGui::GetItemRectMax();
        dl->AddRect(p0, p1, Theme::u32(Theme::C_ACCENT), Theme::ITEM_RADIUS, 0, 1.f);
    }

    ImGui::PopStyleVar(3);
    ImGui::PopStyleColor(5);

    if (enter && buf[0] != '\0') {
        model.addTodo(std::string(buf));
        std::memset(buf, 0, buf_size);
        needs_focus = true;
    }
}