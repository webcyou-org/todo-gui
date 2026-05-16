// Stub for ImGui::PushFont(Font::Enum, float) declared in imgui_user.h.
// bgfx's own imgui.cpp provides the real version (with font atlas lookup),
// but we don't compile that file to avoid the entry framework dependency.
#include <dear-imgui/imgui.h>

namespace ImGui {
    void PushFont(Font::Enum /*_font*/, float _fontSizeBaseUnscaled) {
        ImGui::PushFont(nullptr,
            _fontSizeBaseUnscaled > 0.f ? _fontSizeBaseUnscaled
                                        : ImGui::GetStyle().FontSizeBase);
    }
} // namespace ImGui