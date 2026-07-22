#include "Buffers/BufferLayout.h"

namespace Engine::Buffers
{
    BufferLayout::BufferLayout(std::initializer_list<BufferElement> elements)
        : m_Elements(elements)
    {
        uint32_t offset = 0;
        for (BufferElement& element : m_Elements)
        {
            element.Offset = offset;
            offset += element.ComponentCount * static_cast<uint32_t>(sizeof(float));
        }
        m_Stride = offset;
    }
}
