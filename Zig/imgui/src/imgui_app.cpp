#include "imgui_app.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstring>
#include <cmath>

// Design tokens (mirrors theme.zig)
#define C_BG        IM_COL32(0x1C, 0x1C, 0x1C, 0xFF)
#define C_SURFACE   IM_COL32(0x2A, 0x2A, 0x2A, 0xFF)
#define C_INPUT     IM_COL32(0x30, 0x30, 0x30, 0xFF)
#define C_TEXT      IM_COL32(0xD2, 0xD2, 0xD2, 0xFF)
#define C_WHITE     IM_COL32(0xFF, 0xFF, 0xFF, 0xFF)
#define C_MUTED     IM_COL32(0x9B, 0x9B, 0x9B, 0xFF)
#define C_ACCENT    IM_COL32(0x5D, 0xC2, 0xAF, 0xFF)
#define C_CB_BORDER IM_COL32(0xD9, 0xD9, 0xD9, 0xFF)

#define C_BG_F        ImVec4(0x1C/255.f, 0x1C/255.f, 0x1C/255.f, 1.f)
#define C_INPUT_F     ImVec4(0x30/255.f, 0x30/255.f, 0x30/255.f, 1.f)
#define C_ACCENT_F    ImVec4(0x5D/255.f, 0xC2/255.f, 0xAF/255.f, 1.f)
#define C_TEXT_F      ImVec4(0xD2/255.f, 0xD2/255.f, 0xD2/255.f, 1.f)
#define C_MUTED_F     ImVec4(0x9B/255.f, 0x9B/255.f, 0x9B/255.f, 1.f)
#define C_TRANSP_F    ImVec4(0.f, 0.f, 0.f, 0.f)

static ImFont* g_font_title = nullptr;
static bool    g_input_was_active = false;
static int     g_tab_idx = 0;

static void setup_style() {
    ImGuiStyle& s = ImGui::GetStyle();
    s.WindowRounding  = 0.f;
    s.FrameRounding   = 4.f;
    s.GrabRounding    = 4.f;
    s.WindowBorderSize= 0.f;
    s.WindowPadding   = {24.f, 10.f};
    s.FramePadding    = {16.f,  4.f};
    s.ItemSpacing     = { 8.f,  5.f};
    s.ScrollbarSize   = 8.f;
    s.ScrollbarRounding = 4.f;

    ImVec4* c = s.Colors;
    c[ImGuiCol_WindowBg]         = C_BG_F;
    c[ImGuiCol_Text]             = C_TEXT_F;
    c[ImGuiCol_FrameBg]          = C_INPUT_F;
    c[ImGuiCol_FrameBgHovered]   = ImVec4(0x38/255.f, 0x38/255.f, 0x38/255.f, 1.f);
    c[ImGuiCol_FrameBgActive]    = C_INPUT_F;
    c[ImGuiCol_CheckMark]        = C_ACCENT_F;
    c[ImGuiCol_Header]           = ImVec4(0x2A/255.f, 0x2A/255.f, 0x2A/255.f, 1.f);
    c[ImGuiCol_HeaderHovered]    = ImVec4(0x35/255.f, 0x35/255.f, 0x35/255.f, 1.f);
    c[ImGuiCol_Button]           = C_TRANSP_F;
    c[ImGuiCol_ButtonHovered]    = ImVec4(0.3f, 0.3f, 0.3f, 0.2f);
    c[ImGuiCol_ButtonActive]     = C_TRANSP_F;
    c[ImGuiCol_ScrollbarBg]      = C_BG_F;
    c[ImGuiCol_ScrollbarGrab]    = ImVec4(0x50/255.f, 0x50/255.f, 0x50/255.f, 1.f);
    c[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0x65/255.f, 0x65/255.f, 0x65/255.f, 1.f);
    c[ImGuiCol_ScrollbarGrabActive]  = ImVec4(0x78/255.f, 0x78/255.f, 0x78/255.f, 1.f);
    c[ImGuiCol_Border]           = C_TRANSP_F;
    c[ImGuiCol_Separator]        = ImVec4(0.3f, 0.3f, 0.3f, 1.f);
    c[ImGuiCol_PopupBg]          = C_BG_F;
}

// ─────────────────────────────────────────────────────────────────────────────
void* app_init(int w, int h, const char* title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow* win = glfwCreateWindow(w, h, title, nullptr, nullptr);
    glfwMakeContextCurrent(win);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr; // disable imgui.ini

    const char* font_path = "fonts/Inter.ttf";
    io.Fonts->AddFontFromFileTTF(font_path, 14.f, nullptr, nullptr);
    g_font_title = io.Fonts->AddFontFromFileTTF(font_path, 18.f, nullptr, nullptr);
    if (!g_font_title) g_font_title = io.FontDefault;

    setup_style();

    ImGui_ImplGlfw_InitForOpenGL(win, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    return win;
}

bool app_should_close(void* win) {
    return glfwWindowShouldClose((GLFWwindow*)win);
}

void app_new_frame(void* win) {
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    (void)win;
}

void app_render(void* win) {
    ImGui::Render();
    auto* w = (GLFWwindow*)win;
    int fb_w, fb_h;
    glfwGetFramebufferSize(w, &fb_w, &fb_h);
    glViewport(0, 0, fb_w, fb_h);
    glClearColor(0x1C/255.f, 0x1C/255.f, 0x1C/255.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(w);
}

void app_shutdown(void* win) {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow((GLFWwindow*)win);
    glfwTerminate();
}

// ─────────────────────────────────────────────────────────────────────────────
void app_begin_window() {
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos({0, 0});
    ImGui::SetNextWindowSize(io.DisplaySize);
    ImGui::SetNextWindowBgAlpha(1.f);
    ImGui::Begin("##main", nullptr,
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove     | ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoScrollbar| ImGuiWindowFlags_NoScrollWithMouse);
}

void app_end_window() {
    ImGui::End();
}

// ─────────────────────────────────────────────────────────────────────────────
void app_draw_title(const char* text) {
    if (g_font_title) ImGui::PushFont(g_font_title);
    ImGui::TextColored(ImVec4(1,1,1,1), "%s", text);
    if (g_font_title) ImGui::PopFont();
    ImGui::Dummy({0, 14.f - ImGui::GetStyle().ItemSpacing.y});
}

bool app_draw_input(char* buf, int buf_size) {
    // Border color depends on focus state from previous frame
    ImVec4 border_col = g_input_was_active
        ? ImVec4(0x5D/255.f, 0xC2/255.f, 0xAF/255.f, 1.f)
        : ImVec4(0,0,0,0);

    ImGui::PushStyleColor(ImGuiCol_Border, border_col);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1,1,1,1));

    float avail = ImGui::GetContentRegionAvail().x;
    ImGui::SetNextItemWidth(avail);
    bool entered = ImGui::InputText("##input", buf, (size_t)buf_size,
                                   ImGuiInputTextFlags_EnterReturnsTrue);
    bool active = ImGui::IsItemActive();

    // Draw placeholder when empty and not active
    if (!active && buf[0] == '\0') {
        ImDrawList* dl = ImGui::GetWindowDrawList();
        ImVec2 p = ImGui::GetItemRectMin();
        float h = ImGui::GetItemRectSize().y;
        float font_h = ImGui::GetFontSize();
        dl->AddText({p.x + 16.f, p.y + (h - font_h)/2.f}, C_MUTED, "Add Task");
    }

    g_input_was_active = active;
    ImGui::PopStyleColor(2);
    ImGui::PopStyleVar();
    ImGui::Dummy({0, 14.f - ImGui::GetStyle().ItemSpacing.y});
    return entered;
}

// ─────────────────────────────────────────────────────────────────────────────
void app_begin_tab_row() {
    g_tab_idx = 0;
}

bool app_draw_tab(const char* label, bool active) {
    if (g_tab_idx > 0) ImGui::SameLine(0.f, 0.f);
    g_tab_idx++;

    ImVec4 text_col = active
        ? ImVec4(1, 1, 1, 1)
        : C_TEXT_F;

    float fs = ImGui::GetFontSize();
    float text_w = ImGui::CalcTextSize(label).x;
    float btn_w  = text_w + 8.f * 2;
    float btn_h  = 28.f;

    ImGui::PushStyleColor(ImGuiCol_Text, text_col);
    bool clicked = ImGui::Button(label, {btn_w, btn_h});
    ImGui::PopStyleColor();
    (void)fs;
    return clicked;
}

void app_end_tab_row() {
    ImGui::NewLine();
    ImGui::Dummy({0, 3.f - ImGui::GetStyle().ItemSpacing.y});
}

// ─────────────────────────────────────────────────────────────────────────────
void app_begin_todo_list(float avail_h) {
    ImGui::BeginChild("##todolist", {0, avail_h}, false,
                      ImGuiWindowFlags_NoScrollbar);
}

bool app_draw_todo_item(const char* id_str, const char* text, bool completed) {
    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImVec2 pos = ImGui::GetCursorScreenPos();
    float w = ImGui::GetContentRegionAvail().x;
    const float h = 35.f, pad = 10.f, cb_r = 8.f, cb_margin = 18.f;

    // Reserve full-row hit area
    char item_id[64];
    std::snprintf(item_id, sizeof(item_id), "##item_%s", id_str);
    ImGui::InvisibleButton(item_id, {w, h});
    bool row_clicked = ImGui::IsItemClicked(ImGuiMouseButton_Left);
    ImVec2 mouse_at_click = ImGui::GetMousePos();

    // Background
    dl->AddRectFilled(pos, {pos.x + w, pos.y + h}, C_SURFACE, 4.f);

    // Circular checkbox
    float cb_cx = pos.x + pad + cb_r;
    float cb_cy = pos.y + h / 2.f;
    if (completed) {
        dl->AddCircleFilled({cb_cx, cb_cy}, cb_r, C_ACCENT, 32);
    } else {
        dl->AddCircle({cb_cx, cb_cy}, cb_r, C_CB_BORDER, 32, 2.f);
    }

    // Task text
    float text_x = pos.x + pad + cb_r * 2.f + cb_margin;
    float font_h = ImGui::GetFontSize();
    float text_y = pos.y + (h - font_h) / 2.f;
    ImU32 tc = completed ? C_MUTED : C_TEXT;
    dl->AddText({text_x, text_y}, tc, text);

    // Strikethrough
    if (completed) {
        float tw = ImGui::CalcTextSize(text).x;
        float line_y = text_y + font_h * 0.5f;
        dl->AddLine({text_x, line_y}, {text_x + tw, line_y}, tc, 1.f);
    }

    // Click on checkbox area?
    if (row_clicked) {
        float dx = mouse_at_click.x - cb_cx;
        float dy = mouse_at_click.y - cb_cy;
        float hit_r = cb_r + 6.f;
        if (dx*dx + dy*dy <= hit_r*hit_r) return true;
    }
    return false;
}

void app_end_todo_list() {
    ImGui::EndChild();
}