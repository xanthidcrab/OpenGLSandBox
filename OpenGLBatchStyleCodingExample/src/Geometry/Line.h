#pragma once

#include "Math/MathTypes.h"

namespace Engine::Geometry
{
    // A straight segment between two points. Pure parametric data - no
    // tessellation, no GL.
    struct Line
    {
        Math::Vec3 Start{ 0.0f, 0.0f, 0.0f };
        Math::Vec3 End{ 0.0f, 0.0f, 0.0f };
    };
}
