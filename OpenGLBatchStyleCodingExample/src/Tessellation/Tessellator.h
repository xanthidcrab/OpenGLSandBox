#pragma once

#include "Geometry/AnyGeometry.h"
#include "Geometry/Arc.h"
#include "Geometry/Circle.h"
#include "Geometry/Line.h"
#include "Geometry/Mesh.h"
#include "Geometry/Point.h"
#include "Geometry/Polygon.h"
#include "Geometry/Polyline.h"
#include "Geometry/TessellationSettings.h"
#include "Math/MathTypes.h"

namespace Engine::Tessellation
{
    // Converts parametric Geometry definitions into a CPU-side Mesh.
    // Stateless static utility - no instance, no stored state. This is the
    // only place in the engine that knows how to turn a Circle's
    // center/radius (or an Arc, Polyline, Polygon...) into vertices.
    class Tessellator
    {
    public:
        static Geometry::Mesh Tessellate(
            const Geometry::AnyGeometry& geometry,
            const Geometry::TessellationSettings& settings = {},
            const Math::Vec4& color = Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f));

    private:
        static Geometry::Mesh TessellatePoint(const Geometry::Point& point, const Math::Vec4& color);
        static Geometry::Mesh TessellateLine(const Geometry::Line& line, const Math::Vec4& color);
        static Geometry::Mesh TessellateCircle(const Geometry::Circle& circle, const Geometry::TessellationSettings& settings, const Math::Vec4& color);
        static Geometry::Mesh TessellateArc(const Geometry::Arc& arc, const Geometry::TessellationSettings& settings, const Math::Vec4& color);
        static Geometry::Mesh TessellatePolyline(const Geometry::Polyline& polyline, const Math::Vec4& color);
        static Geometry::Mesh TessellatePolygon(const Geometry::Polygon& polygon, const Math::Vec4& color);
    };
}
