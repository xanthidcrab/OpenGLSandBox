#pragma once

#include "Geometry/Arc.h"
#include "Geometry/Circle.h"
#include "Geometry/Line.h"
#include "Geometry/Point.h"
#include "Geometry/Polygon.h"
#include "Geometry/Polyline.h"

#include <variant>

namespace Engine::Geometry
{
    // The closed set of primary CAD objects, as a tagged union. This is
    // what lets Scene hold heterogeneous entities without inheritance, and
    // what Tessellator dispatches on via std::visit. Adding a new shape
    // means adding it here - every std::visit call site elsewhere will then
    // fail to compile until it handles the new case.
    using AnyGeometry = std::variant<Point, Line, Circle, Arc, Polyline, Polygon>;
}
