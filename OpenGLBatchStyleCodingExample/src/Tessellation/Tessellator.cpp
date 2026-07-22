#include "Tessellation/Tessellator.h"

#include <algorithm>
#include <cmath>
#include <numbers>
#include <variant>

namespace Engine::Tessellation
{
    namespace
    {
        // Combines several lambdas into one callable with overload
        // resolution, so std::visit below can pick the right one by
        // argument type. Standard "overloaded" idiom for std::variant.
        template<typename... Ts>
        struct Overloaded : Ts...
        {
            using Ts::operator()...;
        };
        template<typename... Ts>
        Overloaded(Ts...) -> Overloaded<Ts...>;
    }

    Geometry::Mesh Tessellator::Tessellate(
        const Geometry::AnyGeometry& geometry,
        const Geometry::TessellationSettings& settings,
        const Math::Vec4& color)
    {
        return std::visit(Overloaded{
            [&](const Geometry::Point& point)     { return TessellatePoint(point, color); },
            [&](const Geometry::Line& line)       { return TessellateLine(line, color); },
            [&](const Geometry::Circle& circle)   { return TessellateCircle(circle, settings, color); },
            [&](const Geometry::Arc& arc)         { return TessellateArc(arc, settings, color); },
            [&](const Geometry::Polyline& poly)   { return TessellatePolyline(poly, color); },
            [&](const Geometry::Polygon& polygon) { return TessellatePolygon(polygon, color); },
        }, geometry);
    }

    Geometry::Mesh Tessellator::TessellatePoint(const Geometry::Point& point, const Math::Vec4& color)
    {
        std::vector<Geometry::Vertex> vertices{ Geometry::Vertex(point.Position, color) };
        return Geometry::Mesh(std::move(vertices), Geometry::PrimitiveType::Points);
    }

    Geometry::Mesh Tessellator::TessellateLine(const Geometry::Line& line, const Math::Vec4& color)
    {
        std::vector<Geometry::Vertex> vertices{
            Geometry::Vertex(line.Start, color),
            Geometry::Vertex(line.End, color)
        };
        return Geometry::Mesh(std::move(vertices), Geometry::PrimitiveType::Lines);
    }

    Geometry::Mesh Tessellator::TessellateCircle(const Geometry::Circle& circle, const Geometry::TessellationSettings& settings, const Math::Vec4& color)
    {
        const uint32_t segments = std::max<uint32_t>(settings.CircleSegments, 3);
        const float step = 2.0f * std::numbers::pi_v<float> / static_cast<float>(segments);

        std::vector<Geometry::Vertex> vertices;
        vertices.reserve(static_cast<size_t>(segments) * 3);

        for (uint32_t i = 0; i < segments; ++i)
        {
            const float angle0 = static_cast<float>(i) * step;
            const float angle1 = static_cast<float>(i + 1) * step;

            const Math::Vec3 p0 = circle.Center + Math::Vec3(std::cos(angle0), std::sin(angle0), 0.0f) * circle.Radius;
            const Math::Vec3 p1 = circle.Center + Math::Vec3(std::cos(angle1), std::sin(angle1), 0.0f) * circle.Radius;

            vertices.emplace_back(circle.Center, color);
            vertices.emplace_back(p0, color);
            vertices.emplace_back(p1, color);
        }

        return Geometry::Mesh(std::move(vertices), Geometry::PrimitiveType::Triangles);
    }

    Geometry::Mesh Tessellator::TessellateArc(const Geometry::Arc& arc, const Geometry::TessellationSettings& settings, const Math::Vec4& color)
    {
        const float angleSpan = arc.EndAngleRad - arc.StartAngleRad;
        const float fullTurn = 2.0f * std::numbers::pi_v<float>;
        const uint32_t segments = std::max<uint32_t>(
            1,
            static_cast<uint32_t>(std::ceil(static_cast<float>(settings.CircleSegments) * std::abs(angleSpan) / fullTurn))
        );
        const float step = angleSpan / static_cast<float>(segments);

        std::vector<Geometry::Vertex> vertices;
        vertices.reserve(static_cast<size_t>(segments) * 2);

        for (uint32_t i = 0; i < segments; ++i)
        {
            const float angle0 = arc.StartAngleRad + static_cast<float>(i) * step;
            const float angle1 = arc.StartAngleRad + static_cast<float>(i + 1) * step;

            const Math::Vec3 p0 = arc.Center + Math::Vec3(std::cos(angle0), std::sin(angle0), 0.0f) * arc.Radius;
            const Math::Vec3 p1 = arc.Center + Math::Vec3(std::cos(angle1), std::sin(angle1), 0.0f) * arc.Radius;

            vertices.emplace_back(p0, color);
            vertices.emplace_back(p1, color);
        }

        return Geometry::Mesh(std::move(vertices), Geometry::PrimitiveType::Lines);
    }

    Geometry::Mesh Tessellator::TessellatePolyline(const Geometry::Polyline& polyline, const Math::Vec4& color)
    {
        std::vector<Geometry::Vertex> vertices;
        if (polyline.Points.size() < 2)
            return Geometry::Mesh(std::move(vertices), Geometry::PrimitiveType::Lines);

        vertices.reserve((polyline.Points.size() - 1) * 2);
        for (size_t i = 0; i + 1 < polyline.Points.size(); ++i)
        {
            vertices.emplace_back(polyline.Points[i], color);
            vertices.emplace_back(polyline.Points[i + 1], color);
        }

        return Geometry::Mesh(std::move(vertices), Geometry::PrimitiveType::Lines);
    }

    Geometry::Mesh Tessellator::TessellatePolygon(const Geometry::Polygon& polygon, const Math::Vec4& color)
    {
        std::vector<Geometry::Vertex> vertices;
        if (polygon.Points.size() < 3)
            return Geometry::Mesh(std::move(vertices), Geometry::PrimitiveType::Triangles);

        // Fan triangulation from the first vertex - convex polygons only,
        // per Polygon's documented assumption.
        vertices.reserve((polygon.Points.size() - 2) * 3);
        for (size_t i = 1; i + 1 < polygon.Points.size(); ++i)
        {
            vertices.emplace_back(polygon.Points[0], color);
            vertices.emplace_back(polygon.Points[i], color);
            vertices.emplace_back(polygon.Points[i + 1], color);
        }

        return Geometry::Mesh(std::move(vertices), Geometry::PrimitiveType::Triangles);
    }
}
