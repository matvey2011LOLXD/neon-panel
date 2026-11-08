#include <jni.h>
#include <GLES3/gl3.h>
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"

static bool initialized = false;

extern "C"
JNIEXPORT void JNICALL
Java_com_neon_panel_MainActivity_nativeInit(JNIEnv*, jclass)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 12.0f;
    style.FrameRounding = 7.0f;

    style.Colors[ImGuiCol_WindowBg] =
        ImVec4(0.035f, 0.045f, 0.09f, 1.0f);

    style.Colors[ImGuiCol_Button] =
        ImVec4(0.15f, 0.25f, 0.65f, 1.0f);

    ImGui_ImplOpenGL3_Init("#version 300 es");
    initialized = true;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_neon_panel_MainActivity_nativeResize(
    JNIEnv*, jclass, jint width, jint height)
{
    glViewport(0, 0, width, height);
    ImGui::GetIO().DisplaySize =
        ImVec2((float)width, (float)height);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_neon_panel_MainActivity_nativeRender(JNIEnv*, jclass)
{
    if (!initialized) return;

    glClearColor(0.015f, 0.02f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(420, 300), ImGuiCond_Always);

    ImGui::Begin("NEON PANEL");

    ImGui::TextColored(
        ImVec4(0.25f, 0.55f, 1.0f, 1.0f),
        "NEON PANEL"
    );

    ImGui::Separator();

    static bool enabled = true;
    static float intensity = 0.5f;

    ImGui::Checkbox("Enable interface", &enabled);
    ImGui::SliderFloat("Intensity", &intensity, 0.0f, 1.0f);

    ImGui::Text("OpenGL ES 3.0");
    ImGui::Text("Dear ImGui 1.90.6");

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_neon_panel_MainActivity_nativeTouch(
    JNIEnv*, jclass, jfloat x, jfloat y, jint action)
{
    ImGuiIO& io = ImGui::GetIO();
    io.AddMousePosEvent(x, y);

    if (action == 0)
        io.AddMouseButtonEvent(0, true);

    if (action == 1 || action == 3)
        io.AddMouseButtonEvent(0, false);
}
