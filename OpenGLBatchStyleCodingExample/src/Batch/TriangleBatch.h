#pragma once

#include "Batch/Batch.h"

namespace Engine::Batch
{
    class TriangleBatch : public Batch
    {
    public:
        using Batch::Batch;

    protected:
        Geometry::PrimitiveType GetPrimitiveType() const override { return Geometry::PrimitiveType::Triangles; }
    };
}
