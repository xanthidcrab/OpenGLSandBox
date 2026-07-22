#pragma once

#include "Batch/LineBatch.h"
#include "Batch/PointBatch.h"
#include "Batch/TriangleBatch.h"
#include "Geometry/Mesh.h"
#include "Math/MathTypes.h"
#include "Renderer/RenderState.h"
#include "Renderer/RendererStatistics.h"
#include "Shaders/ShaderProgram.h"

#include <memory>

namespace Engine::Renderer
{
    // The facade: owns every batch and the default shader. Draw(mesh)
    // routes to the matching batch by PrimitiveType - Renderer never knows
    // about Circle/Arc/Polyline/etc, only Mesh (decision 2).
    class Renderer
    {
    public:
        Renderer();

        void BeginScene(const Math::Mat4& viewProjection);
        void Draw(const Geometry::Mesh& mesh);
        void EndScene();

        const RendererStatistics& GetStatistics() const noexcept { return m_Stats; }

    private:
        std::unique_ptr<Shaders::ShaderProgram> m_Shader;
        std::unique_ptr<Batch::PointBatch> m_PointBatch;
        std::unique_ptr<Batch::LineBatch> m_LineBatch;
        std::unique_ptr<Batch::TriangleBatch> m_TriangleBatch;
        RenderState m_RenderState;
        RendererStatistics m_Stats;
    };
}
