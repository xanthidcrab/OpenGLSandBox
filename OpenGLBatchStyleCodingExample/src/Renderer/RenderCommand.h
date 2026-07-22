#pragma once

#include "Geometry/Mesh.h"
#include "Math/MathTypes.h"

#include <cstdint>

namespace Engine::Renderer
{
    // The one and only place raw gl* state/draw-submission calls happen.
    // Stateless static utility, same shape as Tessellator/ShaderProgram's
    // static helpers - no instance, no stored state.
    class RenderCommand
    {
    public:
        static void Init();
        static void SetClearColor(const Math::Vec4& color);
        static void Clear();
        static void SetViewport(int x, int y, int width, int height);
        static void DrawArrays(Geometry::PrimitiveType primitive, uint32_t vertexCount);
    };
}
