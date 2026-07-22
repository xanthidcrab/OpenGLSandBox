#pragma once

#include "Math/MathTypes.h"

namespace Engine::Geometry
{
    // A single CAD point. Pure parametric data - no tessellation, no GL.
    struct Point
    {
        Math::Vec3 Position{ 0.0f, 0.0f, 0.0f };
    };
}
