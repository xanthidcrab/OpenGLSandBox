#pragma once

#include "Geometry/AnyGeometry.h"
#include "Math/MathTypes.h"
#include "Scene/EntityID.h"

namespace Engine::Scene
{
    // A CAD entity: identity + geometry definition + presentation data.
    // Color lives here (not on the Geometry types themselves - see
    // Tessellator's writeup) because it's a per-entity CAD property, not a
    // rendering-quality knob like TessellationSettings.
    struct Entity
    {
        EntityID Id;
        Geometry::AnyGeometry Geometry;
        Math::Vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };
        bool Selected = false;
    };
}
