#pragma once

#include <cstdint>

namespace Engine::Renderer
{
    // Caches the last-bound shader program so redundant glUseProgram calls
    // are skipped. Only shader binding is wired in today (Renderer has a
    // single shader) - VAO-bind caching would follow the same pattern if a
    // future multi-shader/material system needs it.
    class RenderState
    {
    public:
        void BindShaderProgram(uint32_t id);
        void Reset() noexcept;

    private:
        uint32_t m_BoundShaderProgram = 0;
    };
}
