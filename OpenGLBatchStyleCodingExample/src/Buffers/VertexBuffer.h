#pragma once

#include <cstdint>

namespace Engine::Buffers
{
    // RAII wrapper of a GL VBO. Move-only so the GL handle always has
    // exactly one owner.
    class VertexBuffer
    {
    public:
        VertexBuffer(const void* data, uint32_t sizeBytes);
        explicit VertexBuffer(uint32_t sizeBytes); // dynamic, uninitialized
        ~VertexBuffer();

        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer& operator=(const VertexBuffer&) = delete;
        VertexBuffer(VertexBuffer&& other) noexcept;
        VertexBuffer& operator=(VertexBuffer&& other) noexcept;

        void Bind() const;
        void Unbind() const;
        void SetData(const void* data, uint32_t sizeBytes);

        uint32_t GetRendererID() const noexcept { return m_RendererID; }

    private:
        uint32_t m_RendererID = 0;
    };
}
