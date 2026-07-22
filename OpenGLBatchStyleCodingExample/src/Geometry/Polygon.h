#pragma once

#include "Math/MathTypes.h"

#include <vector>

namespace Engine::Geometry
{
    // A closed loop of points, meant to be filled (the last point implicitly
    // connects back to the first). Assumed convex until the Tessellator
    // explicitly supports concave triangulation. Pure parametric data - no
    // tessellation, no GL.
    struct Polygon
    {
        std::vector<Math::Vec3> Points;
    };
}
