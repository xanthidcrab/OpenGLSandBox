#pragma once

#include <string>

struct GLFWwindow;

namespace Engine::Core
{
    // RAII wrapper of a single GLFWwindow + its GL context. Constructor
    // does glfwInit/CreateWindow/MakeContextCurrent/gladLoadGLLoader;
    // destructor destroys the window and calls glfwTerminate. Only one
    // Window is expected to exist at a time (Application owns exactly one).
    class Window
    {
    public:
        struct Props
        {
            std::string Title = "OpenGLBatchStyleCodingExample";
            int Width = 1280;
            int Height = 720;
        };

        explicit Window(const Props& props = {});
        ~Window();

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        bool ShouldClose() const;
        void PollEvents() const;
        void SwapBuffers() const;

        int GetWidth() const noexcept { return m_Width; }
        int GetHeight() const noexcept { return m_Height; }
        GLFWwindow* GetNativeHandle() const noexcept { return m_Handle; }

    private:
        GLFWwindow* m_Handle = nullptr;
        int m_Width = 0;
        int m_Height = 0;
    };
}
