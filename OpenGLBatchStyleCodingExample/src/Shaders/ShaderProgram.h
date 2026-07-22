#pragma once

#include "Math/MathTypes.h"

#include <cstdint>
#include <string>
#include <unordered_map>

namespace Engine::Shaders
{
    // RAII wrapper of a GL shader program. Move-only so the GL handle
    // always has exactly one owner. Uniform locations are cached per name
    // to avoid a glGetUniformLocation round-trip every frame.
    class ShaderProgram
    {
    public:
        ShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
        ~ShaderProgram();

        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;
        ShaderProgram(ShaderProgram&& other) noexcept;
        ShaderProgram& operator=(ShaderProgram&& other) noexcept;

        void Bind() const;
        void Unbind() const;

        void SetMat4(const std::string& name, const Math::Mat4& value);
        void SetVec4(const std::string& name, const Math::Vec4& value);

        uint32_t GetRendererID() const noexcept { return m_RendererID; }

    private:
        int GetUniformLocation(const std::string& name);

        uint32_t m_RendererID = 0;
        std::unordered_map<std::string, int> m_UniformLocationCache;
    };
}
