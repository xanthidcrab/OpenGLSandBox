#include "Renderer/RenderCommand.h"

#include <glad/glad.h>

namespace Engine::Renderer
{
    namespace
    {
        GLenum ToGLPrimitive(Geometry::PrimitiveType primitive)
        {
            switch (primitive)
            {
                case Geometry::PrimitiveType::Points:    return GL_POINTS;
                case Geometry::PrimitiveType::Lines:     return GL_LINES;
                case Geometry::PrimitiveType::Triangles: return GL_TRIANGLES;
            }
            return GL_TRIANGLES;
        }
    }

    void RenderCommand::Init()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void RenderCommand::SetClearColor(const Math::Vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void RenderCommand::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderCommand::SetViewport(int x, int y, int width, int height)
    {
        glViewport(x, y, width, height);
    }

    void RenderCommand::DrawArrays(Geometry::PrimitiveType primitive, uint32_t vertexCount)
    {
        glDrawArrays(ToGLPrimitive(primitive), 0, static_cast<GLsizei>(vertexCount));
    }
}
