#include "Renderer/RenderState.h"

#include <glad/glad.h>

namespace Engine::Renderer
{
    void RenderState::BindShaderProgram(uint32_t id)
    {
        if (id == m_BoundShaderProgram)
            return;

        glUseProgram(id);
        m_BoundShaderProgram = id;
    }

    void RenderState::Reset() noexcept
    {
        m_BoundShaderProgram = 0;
    }
}
