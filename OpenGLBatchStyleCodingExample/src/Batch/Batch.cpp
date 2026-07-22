#include "Batch/Batch.h"
#include "Renderer/RenderCommand.h"

namespace Engine::Batch
{
    Batch::Batch(uint32_t maxVertices, const Buffers::BufferLayout& layout)
        : m_VertexBuffer(maxVertices * static_cast<uint32_t>(sizeof(Geometry::Vertex)))
        , m_MaxVertices(maxVertices)
    {
        m_CPUBuffer.reserve(maxVertices);
        m_VertexArray.SetVertexBuffer(m_VertexBuffer, layout);
    }

    void Batch::Begin()
    {
        m_CPUBuffer.clear();
    }

    void Batch::Add(const Geometry::Vertex& vertex)
    {
        if (m_CPUBuffer.size() >= m_MaxVertices)
            Flush();
        m_CPUBuffer.push_back(vertex);
    }

    void Batch::Add(std::span<const Geometry::Vertex> vertices)
    {
        for (const Geometry::Vertex& vertex : vertices)
            Add(vertex);
    }

    bool Batch::Flush()
    {
        if (m_CPUBuffer.empty())
            return false;

        m_VertexBuffer.SetData(m_CPUBuffer.data(), static_cast<uint32_t>(m_CPUBuffer.size() * sizeof(Geometry::Vertex)));
        m_VertexArray.Bind();
        Renderer::RenderCommand::DrawArrays(GetPrimitiveType(), static_cast<uint32_t>(m_CPUBuffer.size()));
        m_CPUBuffer.clear();
        return true;
    }

    bool Batch::End()
    {
        return Flush();
    }
}
