#pragma once
#include <cstdint>
#include <dear-imgui/imgui.h>

inline ImVec4 col4(float r, float g, float b, float a = 1.f) { return {r, g, b, a}; }

// Converts 0xRRGGBB to ImGui's IM_COL32(r,g,b,a)
#define COL32(hex) IM_COL32(((hex)>>16)&0xFF, ((hex)>>8)&0xFF, (hex)&0xFF, 255)

namespace Theme {
    // Colors as ImGui float4 (r,g,b,a)
    constexpr float BG_R       = 0x1C/255.f, BG_G       = 0x1C/255.f, BG_B       = 0x1C/255.f;
    constexpr float SURFACE_R  = 0x2A/255.f, SURFACE_G  = 0x2A/255.f, SURFACE_B  = 0x2A/255.f;
    constexpr float INPUT_R    = 0x30/255.f, INPUT_G    = 0x30/255.f, INPUT_B    = 0x30/255.f;
    constexpr float TEXT_R     = 0xD2/255.f, TEXT_G     = 0xD2/255.f, TEXT_B     = 0xD2/255.f;
    constexpr float MUTED_R    = 0x9B/255.f, MUTED_G    = 0x9B/255.f, MUTED_B    = 0x9B/255.f;
    constexpr float ACCENT_R   = 0x5D/255.f, ACCENT_G   = 0xC2/255.f, ACCENT_B   = 0xAF/255.f;
    constexpr float CB_BDR_R   = 0xD9/255.f, CB_BDR_G   = 0xD9/255.f, CB_BDR_B   = 0xD9/255.f;

    // IM_COL32 values (premultiplied, alpha=255)
    constexpr uint32_t C_BG       = 0xFF1C1C1C;
    constexpr uint32_t C_SURFACE  = 0xFF2A2A2A;
    constexpr uint32_t C_ACCENT   = 0xFF5DC2AF;
    constexpr uint32_t C_CB_BDR   = 0xFFD9D9D9;
    constexpr uint32_t C_WHITE    = 0xFFFFFFFF;
    constexpr uint32_t C_MUTED    = 0xFF9B9B9B;
    constexpr uint32_t C_TEXT     = 0xFFD2D2D2;

    // Layout
    constexpr int   WIN_W      = 800;
    constexpr int   WIN_H      = 600;
    constexpr float PAD_H      = 24.f;
    constexpr float PAD_V      = 10.f;
    constexpr float TITLE_MB   = 14.f;
    constexpr float INPUT_MB   = 14.f;
    constexpr float TABS_MB    = 3.f;
    constexpr float ITEM_MB    = 5.f;
    constexpr float ITEM_H     = 35.f;
    constexpr float CB_SIZE    = 16.f;
    constexpr float CB_MR      = 18.f;
    constexpr float INPUT_H    = 35.f;
    constexpr float TAB_PX     = 8.f;
    constexpr float TAB_LINE_H = 28.f;
} // namespace Theme