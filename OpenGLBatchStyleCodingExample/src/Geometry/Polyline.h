#pragma once

#include "Math/MathTypes.h"

#include <vector>

namespace Engine::Geometry
{
    // An open, connected sequence of points: N points implies N-1 segments.
    // Deliberately stored as points, not as a list of Line segments - see
    // the class writeup for why. Pure parametric data - no tessellation,
    // no GL.
    struct Polyline
    {
        std::vector<Math::Vec3> Points;
    };
}
