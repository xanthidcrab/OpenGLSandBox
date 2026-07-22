#pragma once

#include "Math/MathTypes.h"

namespace Engine::Geometry
{
    // A circular arc: center + radius, spanning [StartAngleRad, EndAngleRad].
    // Angles are in radians, matching every trig function that will consume
    // them. Pure parametric data - no tessellation, no GL.
    struct Arc
    {
        Math::Vec3 Center{ 0.0f, 0.0f, 0.0f };
        float Radius = 1.0f;
        float StartAngleRad = 0.0f;
        float EndAngleRad = 0.0f;
    };
}
