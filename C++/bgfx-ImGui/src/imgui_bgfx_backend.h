#pragma once
#include <bgfx/bgfx.h>

struct ImDrawData;

// Custom bgfx renderer backend for Dear ImGui.
// Does NOT depend on bgfx's example entry framework.
namespace ImGui_Bgfx {
    bool Init(bgfx::ViewId view_id);
    void Shutdown();
    void RenderDrawData(ImDrawData* draw_data);
} // namespace ImGui_Bgfx