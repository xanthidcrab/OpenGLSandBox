#pragma once

#include <cstdint>

namespace Engine::Geometry
{
    // The rendering-quality knob that Circle/Arc deliberately don't carry
    // themselves (see Circle's writeup). Passed into Tessellator::Tessellate
    // per call, not stored on any geometry value.
    struct TessellationSettings
    {
        uint32_t CircleSegments = 32;
    };
}
