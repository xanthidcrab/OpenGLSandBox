#pragma once

#include "Geometry/Vertex.h"

#include <cstdint>
#include <span>
#include <vector>

namespace Engine::Geometry
{
    // The only primitive shapes a Batch physically knows how to draw.
    // Any geometry with a fancier topology (fans, strips, arcs, splines...)
    // is expected to already be reduced to one of these three by whatever
    // tessellated it - Mesh itself has no opinion on how it got this way.
    enum class PrimitiveType
    {
        Points,
        Lines,
        Triangles
    };

    // The CPU-side, already-tessellated form of a piece of geometry: a flat
    // vertex buffer (+ optional index buffer) tagged with a PrimitiveType.
    // This is the one and only type Renderer knows how to draw, and the one
    // and only type Tessellator knows how to produce. Pure CPU data - no GL
    // handles live here.
    class Mesh
    {
    public:
        Mesh() = default;
        Mesh(std::vector<Vertex> vertices, PrimitiveType primitiveType);
        Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, PrimitiveType primitiveType);

        // Non-owning views. Valid only as long as this Mesh is alive and
        // its internal buffers aren't reallocated - same contract as any
        // std::span/std::string_view.
        std::span<const Vertex> GetVertices() const noexcept;
        std::span<const uint32_t> GetIndices() const noexcept;

        PrimitiveType GetPrimitiveType() const noexcept;
        bool HasIndices() const noexcept;

    private:
        std::vector<Vertex> m_Vertices;
        std::vector<uint32_t> m_Indices;
        PrimitiveType m_PrimitiveType = PrimitiveType::Triangles;
    };
}
