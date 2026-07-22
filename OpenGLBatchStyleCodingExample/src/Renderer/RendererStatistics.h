#pragma once

#include <cstdint>

namespace Engine::Renderer
{
    struct RendererStatistics
    {
        uint32_t DrawCalls = 0;
        uint32_t VertexCount = 0;

        void Reset() noexcept { DrawCalls = 0; VertexCount = 0; }
    };
}
