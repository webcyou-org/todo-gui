#pragma once
#include "imgui.h"

namespace Theme {

// Colors (hex → ImVec4 RGBA)
constexpr ImVec4 C_BG        = {0x1C/255.f, 0x1C/255.f, 0x1C/255.f, 1.f};
constexpr ImVec4 C_SURFACE   = {0x2A/255.f, 0x2A/255.f, 0x2A/255.f, 1.f};
constexpr ImVec4 C_INPUT     = {0x30/255.f, 0x30/255.f, 0x30/255.f, 1.f};
constexpr ImVec4 C_TEXT      = {0xD2/255.f, 0xD2/255.f, 0xD2/255.f, 1.f};
constexpr ImVec4 C_WHITE     = {1.f, 1.f, 1.f, 1.f};
constexpr ImVec4 C_MUTED     = {0x9B/255.f, 0x9B/255.f, 0x9B/255.f, 1.f};
constexpr ImVec4 C_ACCENT    = {0x5D/255.f, 0xC2/255.f, 0xAF/255.f, 1.f};
constexpr ImVec4 C_CB_BORDER = {0xD9/255.f, 0xD9/255.f, 0xD9/255.f, 1.f};
constexpr ImVec4 C_TRANS     = {0.f, 0.f, 0.f, 0.f};

// ImU32 versions (for DrawList)
inline ImU32 u32(ImVec4 c) { return ImGui::ColorConvertFloat4ToU32(c); }

// Sizes
constexpr float WIN_W       = 800.f;
constexpr float WIN_H       = 600.f;
constexpr float PAD_X       = 24.f;
constexpr float PAD_Y       = 10.f;
constexpr float INPUT_H     = 35.f;
constexpr float ITEM_H      = 35.f;
constexpr float ITEM_RADIUS = 4.f;
constexpr float CB_SIZE     = 16.f;
constexpr float CB_RADIUS   = 8.f;
constexpr float CB_MR       = 18.f;   // checkbox margin-right
constexpr float TITLE_MB    = 14.f;
constexpr float INPUT_MB    = 14.f;
constexpr float TAB_MB      = 3.f;
constexpr float ITEM_MB     = 5.f;
constexpr float TAB_PX      = 8.f;
constexpr float TAB_H       = 28.f;
constexpr float FONT_TITLE  = 18.f;
constexpr float FONT_NORMAL = 14.f;

} // namespace Theme