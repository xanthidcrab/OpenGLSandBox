#include "Buffers/VertexBuffer.h"

#include <glad/glad.h>

#include <utility>

namespace Engine::Buffers
{
    VertexBuffer::VertexBuffer(const void* data, uint32_t sizeBytes)
    {
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, sizeBytes, data, GL_STATIC_DRAW);
    }

    VertexBuffer::VertexBuffer(uint32_t sizeBytes)
    {
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, sizeBytes, nullptr, GL_DYNAMIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &m_RendererID);
    }

    VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
        : m_RendererID(std::exchange(other.m_RendererID, 0))
    {
    }

    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
    {
        if (this != &other)
        {
            glDeleteBuffers(1, &m_RendererID);
            m_RendererID = std::exchange(other.m_RendererID, 0);
        }
        return *this;
    }

    void VertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void VertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::SetData(const void* data, uint32_t sizeBytes)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeBytes, data);
    }
}
