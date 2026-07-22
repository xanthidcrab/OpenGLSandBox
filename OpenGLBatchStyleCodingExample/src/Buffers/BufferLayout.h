#pragma once

#include <cstdint>
#include <initializer_list>
#include <span>
#include <string>
#include <vector>

namespace Engine::Buffers
{
    // One vertex attribute (assumes float components, which covers every
    // field Vertex has today - Position and Color are both float vectors).
    struct BufferElement
    {
        std::string Name;
        uint32_t ComponentCount = 0;
        uint32_t Offset = 0;
    };

    // Describes a vertex's attribute layout so glVertexAttribPointer is
    // written in exactly one place (VertexArray::SetVertexBuffer), not
    // scattered across every class that needs to configure a VAO.
    class BufferLayout
    {
    public:
        BufferLayout() = default;
        BufferLayout(std::initializer_list<BufferElement> elements);

        std::span<const BufferElement> GetElements() const noexcept { return m_Elements; }
        uint32_t GetStride() const noexcept { return m_Stride; }

    private:
        std::vector<BufferElement> m_Elements;
        uint32_t m_Stride = 0;
    };
}
