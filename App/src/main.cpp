#include <vector>
#include <iostream>

#include "renderer.hpp"
#include "scene.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

int main(int, char**)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    glfwSetErrorCallback(
        [](int error, const char* description)
        {
            std::cerr << "GLFW error " << error << ": " << description << std::endl;
        }
    );

    if (!glfwInit())
        return 1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "Rasterizer", nullptr, nullptr);;
    if (window == nullptr)
        return 1;

    glfwMakeContextCurrent(window);

    gladLoadGL();

    glfwSwapInterval(1); // Enable vsync
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable viewports

    io.Fonts->AddFontDefault();

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    {
        Renderer* renderer = new Renderer;
        Scene scene;


        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            scene.ShowImGuiControls();
            
            ImGui::Begin("Test");
            ImGui::Text("%f FPS", 1.f / ImGui::GetIO().DeltaTime);
            scene.Update(*renderer);
            ImGui::End();

            // Rendering
            ImGui::Render();
            int displayW, displayH;
            glfwGetFramebufferSize(window, &displayW, &displayH);
            glViewport(0, 0, displayW, displayH);

            glClear(GL_COLOR_BUFFER_BIT);

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            GLFWwindow* ctxBackup = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(ctxBackup);

            glfwSwapBuffers(window);
        }

        delete renderer;
    }

    return 0;
}
