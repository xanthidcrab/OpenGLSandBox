#pragma once

#include "Math/MathTypes.h"

namespace Engine::Camera
{
    // Renderer never knows this type exists - it only ever consumes the
    // resulting mat4 via GetViewProjectionMatrix(). This is what keeps
    // Renderer decoupled from camera types entirely.
    class Camera2D
    {
    public:
        void SetViewportSize(float width, float height) noexcept;
        void SetPosition(const Math::Vec2& position) noexcept { m_Position = position; }
        void SetZoom(float zoom) noexcept { m_Zoom = zoom; }

        Math::Mat4 GetViewProjectionMatrix() const;

    private:
        Math::Vec2 m_Position{ 0.0f, 0.0f };
        float m_Zoom = 5.0f;
        float m_AspectRatio = 1.0f;
    };
}
