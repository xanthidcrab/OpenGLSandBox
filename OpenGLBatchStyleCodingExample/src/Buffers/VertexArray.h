#pragma once

#include "Buffers/BufferLayout.h"

#include <cstdint>

namespace Engine::Buffers
{
    class VertexBuffer;

    // RAII wrapper of a GL VAO. SetVertexBuffer is the one and only place
    // glVertexAttribPointer gets called, driven entirely by BufferLayout.
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        VertexArray(const VertexArray&) = delete;
        VertexArray& operator=(const VertexArray&) = delete;
        VertexArray(VertexArray&& other) noexcept;
        VertexArray& operator=(VertexArray&& other) noexcept;

        void Bind() const;
        void Unbind() const;
        void SetVertexBuffer(const VertexBuffer& vertexBuffer, const BufferLayout& layout);

        uint32_t GetRendererID() const noexcept { return m_RendererID; }

    private:
        uint32_t m_RendererID = 0;
    };
}
