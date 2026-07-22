#include "Geometry/Mesh.h"

namespace Engine::Geometry
{
    Mesh::Mesh(std::vector<Vertex> vertices, PrimitiveType primitiveType)
        : m_Vertices(std::move(vertices)), m_PrimitiveType(primitiveType)
    {
    }

    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, PrimitiveType primitiveType)
        : m_Vertices(std::move(vertices)), m_Indices(std::move(indices)), m_PrimitiveType(primitiveType)
    {
    }

    std::span<const Vertex> Mesh::GetVertices() const noexcept
    {
        return m_Vertices;
    }

    std::span<const uint32_t> Mesh::GetIndices() const noexcept
    {
        return m_Indices;
    }

    PrimitiveType Mesh::GetPrimitiveType() const noexcept
    {
        return m_PrimitiveType;
    }

    bool Mesh::HasIndices() const noexcept
    {
        return !m_Indices.empty();
    }
}
