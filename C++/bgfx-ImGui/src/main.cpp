// bgfx needs the native window handle before init
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

// Dear ImGui (from bgfx's bundled 3rdparty)
#include <dear-imgui/imgui.h>

#include "imgui_bgfx_backend.h"
#include "metal_window.h"
#include "data.h"
#include "theme.h"
#include "widgets/input.h"
#include "widgets/tabs.h"
#include "widgets/todo_item.h"

// Roboto font binary (from bgfx examples)
#include "imgui/roboto_regular.ttf.h"

#include <cstdlib>
#include <cstring>
#include <string>

// ─── App state ───────────────────────────────────────────────────────────────

static TodoModel g_model;
static TabFilter g_tab   = TabFilter::All;
static char      g_input[256] = {};

// ─── Style setup ─────────────────────────────────────────────────────────────

static void setup_style() {
    ImGuiStyle& s = ImGui::GetStyle();
    ImVec4*     c = s.Colors;

    c[ImGuiCol_WindowBg]         = col4(Theme::BG_R,     Theme::BG_G,     Theme::BG_B);
    c[ImGuiCol_FrameBg]          = col4(Theme::INPUT_R,  Theme::INPUT_G,  Theme::INPUT_B);
    c[ImGuiCol_FrameBgHovered]   = col4(Theme::INPUT_R,  Theme::INPUT_G,  Theme::INPUT_B);
    c[ImGuiCol_FrameBgActive]    = col4(Theme::INPUT_R,  Theme::INPUT_G,  Theme::INPUT_B);
    c[ImGuiCol_Text]             = col4(Theme::TEXT_R,   Theme::TEXT_G,   Theme::TEXT_B);
    c[ImGuiCol_TextSelectedBg]   = col4(Theme::ACCENT_R, Theme::ACCENT_G, Theme::ACCENT_B, 0.35f);
    c[ImGuiCol_Border]           = col4(0, 0, 0, 0);
    c[ImGuiCol_BorderShadow]     = col4(0, 0, 0, 0);
    c[ImGuiCol_ScrollbarBg]      = col4(Theme::BG_R,     Theme::BG_G,     Theme::BG_B);
    c[ImGuiCol_ScrollbarGrab]        = col4(0.3f, 0.3f, 0.3f);
    c[ImGuiCol_ScrollbarGrabHovered] = col4(0.35f, 0.35f, 0.35f);
    c[ImGuiCol_ScrollbarGrabActive]  = col4(0.4f,  0.4f,  0.4f);
    c[ImGuiCol_Button]           = col4(0, 0, 0, 0);
    c[ImGuiCol_ButtonHovered]    = col4(1, 1, 1, 0.05f);
    c[ImGuiCol_ButtonActive]     = col4(1, 1, 1, 0.10f);

    s.WindowPadding    = {Theme::PAD_H, Theme::PAD_V};
    s.FramePadding     = {16.f, 4.f};
    s.ItemSpacing      = {0.f, 0.f};
    s.FrameRounding    = 4.f;
    s.WindowRounding   = 0.f;
    s.WindowBorderSize = 0.f;
    s.FrameBorderSize  = 0.f;
    s.ScrollbarSize    = 8.f;
}

// ─── GLFW callbacks ───────────────────────────────────────────────────────────

static void glfw_mouse_btn_cb(GLFWwindow*, int button, int action, int /*mods*/) {
    ImGuiIO& io  = ImGui::GetIO();
    int imgui_btn = (button == GLFW_MOUSE_BUTTON_LEFT)   ? ImGuiMouseButton_Left   :
                   (button == GLFW_MOUSE_BUTTON_RIGHT)  ? ImGuiMouseButton_Right  :
                   (button == GLFW_MOUSE_BUTTON_MIDDLE) ? ImGuiMouseButton_Middle : -1;
    if (imgui_btn >= 0)
        io.AddMouseButtonEvent(imgui_btn, action == GLFW_PRESS);
}

static void glfw_scroll_cb(GLFWwindow*, double xoff, double yoff) {
    ImGui::GetIO().AddMouseWheelEvent((float)xoff, (float)yoff);
}

static void glfw_key_cb(GLFWwindow*, int key, int /*scancode*/, int action, int mods) {
    if (action == GLFW_RELEASE) return;
    ImGuiIO& io = ImGui::GetIO();
    io.AddKeyEvent(ImGuiMod_Ctrl,  (mods & GLFW_MOD_CONTROL) != 0);
    io.AddKeyEvent(ImGuiMod_Shift, (mods & GLFW_MOD_SHIFT)   != 0);
    ImGuiKey ik = ImGuiKey_None;
    switch (key) {
        case GLFW_KEY_BACKSPACE: ik = ImGuiKey_Backspace;  break;
        case GLFW_KEY_DELETE:    ik = ImGuiKey_Delete;     break;
        case GLFW_KEY_LEFT:      ik = ImGuiKey_LeftArrow;  break;
        case GLFW_KEY_RIGHT:     ik = ImGuiKey_RightArrow; break;
        case GLFW_KEY_HOME:      ik = ImGuiKey_Home;       break;
        case GLFW_KEY_END:       ik = ImGuiKey_End;        break;
        case GLFW_KEY_ENTER:
        case GLFW_KEY_KP_ENTER:  ik = ImGuiKey_Enter;      break;
        case GLFW_KEY_ESCAPE:    ik = ImGuiKey_Escape;     break;
        case GLFW_KEY_TAB:       ik = ImGuiKey_Tab;        break;
        case GLFW_KEY_A:         ik = ImGuiKey_A;          break;
        case GLFW_KEY_C:         ik = ImGuiKey_C;          break;
        case GLFW_KEY_V:         ik = ImGuiKey_V;          break;
        case GLFW_KEY_X:         ik = ImGuiKey_X;          break;
        case GLFW_KEY_Z:         ik = ImGuiKey_Z;          break;
    }
    if (ik != ImGuiKey_None) io.AddKeyEvent(ik, true);
}

static void glfw_char_cb(GLFWwindow*, unsigned int c) {
    ImGui::GetIO().AddInputCharacter(c);
}

// ─── Main ─────────────────────────────────────────────────────────────────────

int main() {
    if (!glfwInit()) return 1;

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // bgfx manages the renderer
    glfwWindowHint(GLFW_RESIZABLE,  GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(
        Theme::WIN_W, Theme::WIN_H, "ToDo", nullptr, nullptr);
    if (!window) { glfwTerminate(); return 1; }

    // Create CAMetalLayer explicitly. bgfx accepts NSWindow, NSView, or CAMetalLayer.
    // Creating the layer upfront on the main thread avoids a run-loop deadlock where
    // bgfx's render thread tries to dispatch setLayer: to the blocked main run loop.
    // nwh must be set on bgfx::Init (not via bgfx::setPlatformData) for it to be seen.
    void* metalLayer = metal_create_layer(glfwGetCocoaWindow(window),
                                          Theme::WIN_W, Theme::WIN_H);

    // Single-threaded mode: bgfx::renderFrame() before init tells bgfx to use the
    // calling (main) thread as the render thread, avoiding any thread-dispatch issues.
    bgfx::renderFrame();

    bgfx::Init init;
    init.type              = bgfx::RendererType::Metal;
    init.platformData.nwh  = metalLayer;
    init.resolution.width  = (uint32_t)Theme::WIN_W;
    init.resolution.height = (uint32_t)Theme::WIN_H;
    init.resolution.reset  = BGFX_RESET_VSYNC;
    if (!bgfx::init(init)) return 1;

    // View 0: background clear
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x1C1C1CFF, 1.f, 0);
    bgfx::setViewRect(0, 0, 0, (uint16_t)Theme::WIN_W, (uint16_t)Theme::WIN_H);

    // View 255: Dear ImGui rendering
    constexpr bgfx::ViewId kImguiView = 255;
    bgfx::setViewRect(kImguiView, 0, 0,
                      (uint16_t)Theme::WIN_W, (uint16_t)Theme::WIN_H);
    bgfx::setViewMode(kImguiView, bgfx::ViewMode::Sequential);

    // Provide allocators before CreateContext (imconfig.h disables defaults)
    ImGui::SetAllocatorFunctions(
        [](size_t sz, void*) -> void* { return std::malloc(sz); },
        [](void* p, void*)             { std::free(p); },
        nullptr);

    // Dear ImGui init
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.DisplaySize = {(float)Theme::WIN_W, (float)Theme::WIN_H};

    // Load Roboto font from bgfx's bundled TTF data
    ImFontConfig fc;
    fc.FontDataOwnedByAtlas = false;
    io.Fonts->AddFontFromMemoryTTF(
        const_cast<uint8_t*>(s_robotoRegularTtf),
        (int)sizeof(s_robotoRegularTtf), 14.f, &fc);

    setup_style();

    // Init backend — sets ImGuiBackendFlags_RendererHasTextures internally
    if (!ImGui_Bgfx::Init(kImguiView)) return 1;

    // GLFW input callbacks
    glfwSetMouseButtonCallback(window, glfw_mouse_btn_cb);
    glfwSetScrollCallback(window,      glfw_scroll_cb);
    glfwSetKeyCallback(window,         glfw_key_cb);
    glfwSetCharCallback(window,        glfw_char_cb);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Update Dear ImGui IO
        double mx, my;
        glfwGetCursorPos(window, &mx, &my);
        io.AddMousePosEvent((float)mx, (float)my);
        io.DeltaTime = 1.f / 60.f; // approximate

        // Begin ImGui frame
        ImGui::NewFrame();

        // Full-screen frameless window
        ImGui::SetNextWindowPos({0.f, 0.f});
        ImGui::SetNextWindowSize({(float)Theme::WIN_W, (float)Theme::WIN_H});
        ImGui::Begin("##root", nullptr,
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoResize     |
            ImGuiWindowFlags_NoBringToFrontOnFocus);

        // ── Title ──────────────────────────────────────────────────────────
        ImVec2 title_pos  = ImGui::GetCursorScreenPos();
        float  title_size = 18.f;
        ImGui::PushFont(nullptr, title_size);
        ImGui::PushStyleColor(ImGuiCol_Text, col4(1.f, 1.f, 1.f));
        ImGui::TextUnformatted("ToDo");
        // Pseudo-bold: second pass offset 0.4 px
        ImGui::GetWindowDrawList()->AddText(
            ImGui::GetFont(), title_size,
            {title_pos.x + 0.4f, title_pos.y},
            IM_COL32(255, 255, 255, 255), "ToDo");
        ImGui::PopStyleColor();
        ImGui::PopFont();

        ImGui::Dummy({0.f, Theme::TITLE_MB});

        render_input(g_model, g_input, sizeof(g_input));
        render_tabs(g_tab);
        render_todo_list(g_model, g_tab);

        ImGui::End();

        // Render
        ImGui::Render();
        ImGui_Bgfx::RenderDrawData(ImGui::GetDrawData());

        bgfx::touch(0);
        bgfx::frame();
    }

    ImGui_Bgfx::Shutdown();
    ImGui::DestroyContext();
    bgfx::shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}