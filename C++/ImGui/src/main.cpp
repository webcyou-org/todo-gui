#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include "data.h"
#include "theme.h"
#include "widgets/todo_input.h"
#include "widgets/tab_menu.h"
#include "widgets/todo_list.h"

// ── Global state ──────────────────────────────────────────────────────────────

static TodoModel g_todos;
static MenuModel g_menu;
static char      g_input_buf[256] = {};
static bool      g_needs_focus    = true;

static ImFont* g_font_regular  = nullptr;
static ImFont* g_font_bold_14  = nullptr;
static ImFont* g_font_bold_18  = nullptr;

// ── Render ────────────────────────────────────────────────────────────────────

static void render_app() {
    ImGui::SetNextWindowPos({0, 0});
    ImGui::SetNextWindowSize({Theme::WIN_W, Theme::WIN_H});

    ImGui::PushStyleColor(ImGuiCol_WindowBg, Theme::C_BG);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding,    {Theme::PAD_X, Theme::PAD_Y});
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding,   0.f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);

    constexpr ImGuiWindowFlags kFlags =
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove     | ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("##app", nullptr, kFlags);
    ImGui::PopStyleColor();
    ImGui::PopStyleVar(3);

    // Title
    ImGui::PushFont(g_font_bold_18);
    ImGui::PushStyleColor(ImGuiCol_Text, Theme::C_WHITE);
    ImGui::Text("ToDo");
    ImGui::PopStyleColor();
    ImGui::PopFont();
    ImGui::Dummy({0.f, Theme::TITLE_MB});

    // Input
    render_todo_input(g_todos, g_input_buf, sizeof(g_input_buf),
                      g_needs_focus, g_font_bold_14);
    ImGui::Dummy({0.f, Theme::INPUT_MB});

    // Tabs
    render_tab_menu(g_menu, g_font_bold_14);
    ImGui::Dummy({0.f, Theme::TAB_MB});

    // Todo list
    render_todo_list(g_todos, g_menu.activeTab());

    ImGui::End();
}

// ── Main ──────────────────────────────────────────────────────────────────────

int main() {
    if (!glfwInit()) return 1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,   GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(
        static_cast<int>(Theme::WIN_W),
        static_cast<int>(Theme::WIN_H),
        "ToDo", nullptr, nullptr);
    if (!window) { glfwTerminate(); return 1; }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // HiDPI support
    float dpi = 1.f;
    glfwGetWindowContentScale(window, &dpi, nullptr);

    const char* font_r = "/Library/Fonts/Microsoft/Arial.ttf";
    const char* font_b = "/Library/Fonts/Microsoft/Arial Bold.ttf";

    g_font_regular = io.Fonts->AddFontFromFileTTF(font_r, Theme::FONT_NORMAL * dpi);
    g_font_bold_14 = io.Fonts->AddFontFromFileTTF(font_b, Theme::FONT_NORMAL * dpi);
    g_font_bold_18 = io.Fonts->AddFontFromFileTTF(font_b, Theme::FONT_TITLE  * dpi);

    if (!g_font_regular) { g_font_regular = io.Fonts->AddFontDefault(); }
    if (!g_font_bold_14) g_font_bold_14 = g_font_regular;
    if (!g_font_bold_18) g_font_bold_18 = g_font_regular;

    io.FontGlobalScale = 1.f / dpi;

    // Style
    ImGui::StyleColorsDark();
    ImGuiStyle& s = ImGui::GetStyle();
    s.ItemSpacing     = {0.f, 0.f};
    s.ScrollbarSize   = 8.f;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        render_app();

        ImGui::Render();
        int fb_w, fb_h;
        glfwGetFramebufferSize(window, &fb_w, &fb_h);
        glViewport(0, 0, fb_w, fb_h);
        glClearColor(0.11f, 0.11f, 0.11f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
