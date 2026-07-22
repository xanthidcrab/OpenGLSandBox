#include "Renderer/Renderer.h"
#include "Buffers/BufferLayout.h"

namespace Engine::Renderer
{
    namespace
    {
        // Inlined for now rather than loaded from Assets/ via a
        // Utilities::FileReader - deliberate scope cut to get a working
        // vertical slice quickly; revisit once a file-loading pipeline is
        // actually needed by more than one shader.
        const char* VertexSource = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;

            out vec4 v_Color;

            void main()
            {
                v_Color = a_Color;
                gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
                gl_PointSize = 4.0;
            }
        )";

        const char* FragmentSource = R"(
            #version 330 core
            in vec4 v_Color;
            out vec4 o_Color;

            void main()
            {
                o_Color = v_Color;
            }
        )";

        constexpr uint32_t MaxVerticesPerBatch = 10000;
    }

    Renderer::Renderer()
        : m_Shader(std::make_unique<Shaders::ShaderProgram>(VertexSource, FragmentSource))
    {
        Buffers::BufferLayout layout{
            { "a_Position", 3 },
            { "a_Color", 4 },
        };

        m_PointBatch = std::make_unique<Batch::PointBatch>(MaxVerticesPerBatch, layout);
        m_LineBatch = std::make_unique<Batch::LineBatch>(MaxVerticesPerBatch, layout);
        m_TriangleBatch = std::make_unique<Batch::TriangleBatch>(MaxVerticesPerBatch, layout);
    }

    void Renderer::BeginScene(const Math::Mat4& viewProjection)
    {
        m_Stats.Reset();

        m_RenderState.BindShaderProgram(m_Shader->GetRendererID());
        m_Shader->SetMat4("u_ViewProjection", viewProjection);

        m_PointBatch->Begin();
        m_LineBatch->Begin();
        m_TriangleBatch->Begin();
    }

    void Renderer::Draw(const Geometry::Mesh& mesh)
    {
        switch (mesh.GetPrimitiveType())
        {
            case Geometry::PrimitiveType::Points:
                m_PointBatch->Add(mesh.GetVertices());
                break;
            case Geometry::PrimitiveType::Lines:
                m_LineBatch->Add(mesh.GetVertices());
                break;
            case Geometry::PrimitiveType::Triangles:
                m_TriangleBatch->Add(mesh.GetVertices());
                break;
        }

        m_Stats.VertexCount += static_cast<uint32_t>(mesh.GetVertices().size());
    }

    void Renderer::EndScene()
    {
        if (m_PointBatch->End()) m_Stats.DrawCalls++;
        if (m_LineBatch->End()) m_Stats.DrawCalls++;
        if (m_TriangleBatch->End()) m_Stats.DrawCalls++;
    }
}
