#include "Buffers/VertexArray.h"
#include "Buffers/VertexBuffer.h"

#include <glad/glad.h>

#include <utility>

namespace Engine::Buffers
{
    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &m_RendererID);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    VertexArray::VertexArray(VertexArray&& other) noexcept
        : m_RendererID(std::exchange(other.m_RendererID, 0))
    {
    }

    VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
    {
        if (this != &other)
        {
            glDeleteVertexArrays(1, &m_RendererID);
            m_RendererID = std::exchange(other.m_RendererID, 0);
        }
        return *this;
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }

    void VertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void VertexArray::SetVertexBuffer(const VertexBuffer& vertexBuffer, const BufferLayout& layout)
    {
        glBindVertexArray(m_RendererID);
        vertexBuffer.Bind();

        uint32_t attribIndex = 0;
        for (const BufferElement& element : layout.GetElements())
        {
            glEnableVertexAttribArray(attribIndex);
            glVertexAttribPointer(
                attribIndex,
                static_cast<GLint>(element.ComponentCount),
                GL_FLOAT,
                GL_FALSE,
                static_cast<GLsizei>(layout.GetStride()),
                reinterpret_cast<const void*>(static_cast<uintptr_t>(element.Offset))
            );
            ++attribIndex;
        }
    }
}
