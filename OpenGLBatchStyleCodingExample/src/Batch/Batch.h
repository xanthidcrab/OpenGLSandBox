#pragma once

#include "Buffers/BufferLayout.h"
#include "Buffers/VertexArray.h"
#include "Buffers/VertexBuffer.h"
#include "Geometry/Mesh.h"
#include "Geometry/Vertex.h"

#include <span>
#include <vector>

namespace Engine::Batch
{
    // Owns one VAO + one dynamic VBO + a CPU staging buffer. Concrete,
    // non-template, over Engine::Geometry::Vertex - decision 5 already
    // collapsed every vertex to one type, so a Batch<VertexT> template
    // would have exactly one instantiation today; adding the template back
    // is a mechanical change if a second vertex type (e.g. for TextBatch)
    // is ever actually needed.
    class Batch
    {
    public:
        Batch(uint32_t maxVertices, const Buffers::BufferLayout& layout);
        virtual ~Batch() = default;

        Batch(const Batch&) = delete;
        Batch& operator=(const Batch&) = delete;

        void Begin();
        void Add(const Geometry::Vertex& vertex);
        void Add(std::span<const Geometry::Vertex> vertices);

        // Returns true if a draw call was actually issued (false if the
        // batch had nothing queued) - Renderer uses this to count draw
        // calls in RendererStatistics.
        bool Flush();
        bool End();

    protected:
        virtual Geometry::PrimitiveType GetPrimitiveType() const = 0;

    private:
        Buffers::VertexArray m_VertexArray;
        Buffers::VertexBuffer m_VertexBuffer;
        std::vector<Geometry::Vertex> m_CPUBuffer;
        uint32_t m_MaxVertices;
    };
}
