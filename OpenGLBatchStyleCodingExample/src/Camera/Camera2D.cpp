#include "Camera/Camera2D.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Engine::Camera
{
    void Camera2D::SetViewportSize(float width, float height) noexcept
    {
        m_AspectRatio = (height != 0.0f) ? (width / height) : 1.0f;
    }

    Math::Mat4 Camera2D::GetViewProjectionMatrix() const
    {
        Math::Mat4 projection = glm::ortho(
            -m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom,
            -m_Zoom, m_Zoom,
            -1.0f, 1.0f
        );
        Math::Mat4 view = glm::translate(Math::Mat4(1.0f), Math::Vec3(-m_Position.x, -m_Position.y, 0.0f));
        return projection * view;
    }
}
