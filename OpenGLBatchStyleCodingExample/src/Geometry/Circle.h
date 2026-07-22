#pragma once

#include "Math/MathTypes.h"

namespace Engine::Geometry
{
    // A circle defined purely by its geometric truth: center and radius.
    // How finely it gets tessellated into triangles is a rendering-quality
    // concern, not a property of the shape - see Tessellation::Tessellator.
    struct Circle
    {
        Math::Vec3 Center{ 0.0f, 0.0f, 0.0f };
        float Radius = 1.0f;
    };
}
