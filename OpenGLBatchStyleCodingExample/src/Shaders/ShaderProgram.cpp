#include "Shaders/ShaderProgram.h"

#include <glad/glad.h>

#include <array>
#include <iostream>
#include <utility>
#include <vector>

namespace Engine::Shaders
{
    namespace
    {
        uint32_t CompileStage(GLenum stage, const std::string& source)
        {
            uint32_t shader = glCreateShader(stage);
            const char* src = source.c_str();
            glShaderSource(shader, 1, &src, nullptr);
            glCompileShader(shader);

            int success = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                int length = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
                std::vector<char> log(static_cast<size_t>(length));
                glGetShaderInfoLog(shader, length, nullptr, log.data());
                std::cerr << "[ShaderProgram] compile error: " << log.data() << std::endl;
                glDeleteShader(shader);
                return 0;
            }
            return shader;
        }
    }

    ShaderProgram::ShaderProgram(const std::string& vertexSource, const std::string& fragmentSource)
    {
        uint32_t vertexShader = CompileStage(GL_VERTEX_SHADER, vertexSource);
        uint32_t fragmentShader = CompileStage(GL_FRAGMENT_SHADER, fragmentSource);

        m_RendererID = glCreateProgram();
        glAttachShader(m_RendererID, vertexShader);
        glAttachShader(m_RendererID, fragmentShader);
        glLinkProgram(m_RendererID);

        int success = 0;
        glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
        if (!success)
        {
            int length = 0;
            glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> log(static_cast<size_t>(length));
            glGetProgramInfoLog(m_RendererID, length, nullptr, log.data());
            std::cerr << "[ShaderProgram] link error: " << log.data() << std::endl;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(m_RendererID);
    }

    ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
        : m_RendererID(std::exchange(other.m_RendererID, 0))
        , m_UniformLocationCache(std::move(other.m_UniformLocationCache))
    {
    }

    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept
    {
        if (this != &other)
        {
            glDeleteProgram(m_RendererID);
            m_RendererID = std::exchange(other.m_RendererID, 0);
            m_UniformLocationCache = std::move(other.m_UniformLocationCache);
        }
        return *this;
    }

    void ShaderProgram::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void ShaderProgram::Unbind() const
    {
        glUseProgram(0);
    }

    int ShaderProgram::GetUniformLocation(const std::string& name)
    {
        auto it = m_UniformLocationCache.find(name);
        if (it != m_UniformLocationCache.end())
            return it->second;

        int location = glGetUniformLocation(m_RendererID, name.c_str());
        m_UniformLocationCache[name] = location;
        return location;
    }

    void ShaderProgram::SetMat4(const std::string& name, const Math::Mat4& value)
    {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]);
    }

    void ShaderProgram::SetVec4(const std::string& name, const Math::Vec4& value)
    {
        glUniform4fv(GetUniformLocation(name), 1, &value[0]);
    }
}
