#include "Core/Application.h"
#include "Renderer/RenderCommand.h"

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace Engine::Core
{
    Application::Application(std::unique_ptr<IExample> example, const Window::Props& windowProps)
        : m_Window(windowProps)
        , m_Example(std::move(example))
    {
        Renderer::RenderCommand::Init();
        m_Camera.SetViewportSize(static_cast<float>(m_Window.GetWidth()), static_cast<float>(m_Window.GetHeight()));

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(m_Window.GetNativeHandle(), true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    Application::~Application()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void Application::Run()
    {
        m_Example->OnAttach();

        double lastTime = glfwGetTime();
        while (!m_Window.ShouldClose())
        {
            double now = glfwGetTime();
            float deltaTime = static_cast<float>(now - lastTime);
            lastTime = now;

            m_Window.PollEvents();

            m_Camera.SetViewportSize(static_cast<float>(m_Window.GetWidth()), static_cast<float>(m_Window.GetHeight()));
            Renderer::RenderCommand::SetViewport(0, 0, m_Window.GetWidth(), m_Window.GetHeight());
            Renderer::RenderCommand::SetClearColor(Math::Vec4(0.1f, 0.1f, 0.12f, 1.0f));
            Renderer::RenderCommand::Clear();

            m_Example->OnUpdate(deltaTime);

            m_Renderer.BeginScene(m_Camera.GetViewProjectionMatrix());
            m_Example->OnRender(m_Renderer);
            m_Renderer.EndScene();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            m_Example->OnImGuiRender();
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            m_Window.SwapBuffers();
        }

        m_Example->OnDetach();
    }
}
