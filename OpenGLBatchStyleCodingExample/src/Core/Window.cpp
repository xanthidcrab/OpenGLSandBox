#include "Core/Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdexcept>

namespace Engine::Core
{
    Window::Window(const Props& props)
        : m_Width(props.Width), m_Height(props.Height)
    {
        if (!glfwInit())
            throw std::runtime_error("Window: glfwInit failed");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_Handle = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);
        if (!m_Handle)
        {
            glfwTerminate();
            throw std::runtime_error("Window: glfwCreateWindow failed");
        }

        glfwSetWindowUserPointer(m_Handle, this);
        glfwMakeContextCurrent(m_Handle);
        glfwSwapInterval(1);

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            glfwDestroyWindow(m_Handle);
            glfwTerminate();
            throw std::runtime_error("Window: gladLoadGLLoader failed");
        }

        glfwSetFramebufferSizeCallback(m_Handle, [](GLFWwindow* handle, int width, int height)
        {
            auto* self = static_cast<Window*>(glfwGetWindowUserPointer(handle));
            if (self)
            {
                self->m_Width = width;
                self->m_Height = height;
            }
        });
    }

    Window::~Window()
    {
        if (m_Handle)
            glfwDestroyWindow(m_Handle);
        glfwTerminate();
    }

    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(m_Handle) != 0;
    }

    void Window::PollEvents() const
    {
        glfwPollEvents();
    }

    void Window::SwapBuffers() const
    {
        glfwSwapBuffers(m_Handle);
    }
}
