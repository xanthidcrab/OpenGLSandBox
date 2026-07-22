#pragma once

#include "Math/MathTypes.h"

namespace Engine::Geometry
{
    // The single vertex format used everywhere in the renderer: every
    // Buffer, every Batch, every Mesh, every BufferLayout speaks Vertex.
    // 2D geometry sets Position.z = 0.0f; there is no parallel Vertex2D.
    struct Vertex
    {
        Math::Vec3 Position{ 0.0f, 0.0f, 0.0f };
        Math::Vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

        Vertex() = default;
        Vertex(const Math::Vec3& position, const Math::Vec4& color)
            : Position(position), Color(color)
        {
        }

        bool operator==(const Vertex& other) const
        {
            return Position == other.Position && Color == other.Color;
        }
    };
}
