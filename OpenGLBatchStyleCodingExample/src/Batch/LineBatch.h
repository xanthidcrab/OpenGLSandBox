#pragma once

#include "Batch/Batch.h"

namespace Engine::Batch
{
    class LineBatch : public Batch
    {
    public:
        using Batch::Batch;

    protected:
        Geometry::PrimitiveType GetPrimitiveType() const override { return Geometry::PrimitiveType::Lines; }
    };
}
