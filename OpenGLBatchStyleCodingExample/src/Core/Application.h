#pragma once

#include "Camera/Camera2D.h"
#include "Core/IExample.h"
#include "Core/Window.h"
#include "Renderer/Renderer.h"

#include <memory>

namespace Engine::Core
{
    // Owns Window + Renderer + the current IExample, runs the main loop,
    // and never calls gl* itself - every OpenGL call happens inside
    // Renderer/Batch/Buffers/RenderCommand. Also owns the ImGui backend
    // lifetime (init in ctor, NewFrame/Render each iteration, shutdown in
    // dtor) so individual Examples can just implement OnImGuiRender().
    class Application
    {
    public:
        explicit Application(std::unique_ptr<IExample> example, const Window::Props& windowProps = {});
        ~Application();

        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;

        void Run();

    private:
        Window m_Window;
        Renderer::Renderer m_Renderer;
        Camera::Camera2D m_Camera;
        std::unique_ptr<IExample> m_Example;
    };
}
