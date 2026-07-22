#include "SceneEditorExample.h"

#include "Renderer/Renderer.h"
#include "Tessellation/Tessellator.h"

#include <imgui.h>

#include <cstdio>
#include <variant>
#include <vector>

namespace Examples
{
    using namespace Engine;

    namespace
    {
        const char* GeometryTypeName(const Geometry::AnyGeometry& geometry)
        {
            return std::visit(
                [](auto&& shape) -> const char*
                {
                    using T = std::decay_t<decltype(shape)>;
                    if constexpr (std::is_same_v<T, Geometry::Point>)    return "Point";
                    else if constexpr (std::is_same_v<T, Geometry::Line>)     return "Line";
                    else if constexpr (std::is_same_v<T, Geometry::Circle>)   return "Circle";
                    else if constexpr (std::is_same_v<T, Geometry::Arc>)      return "Arc";
                    else if constexpr (std::is_same_v<T, Geometry::Polyline>) return "Polyline";
                    else if constexpr (std::is_same_v<T, Geometry::Polygon>)  return "Polygon";
                },
                geometry);
        }
    }

    void SceneEditorExample::OnAttach()
    {
        m_Scene.CreateEntity(Geometry::Circle{ Math::Vec3(-2.0f, 0.0f, 0.0f), 0.8f }, Math::Vec4(0.9f, 0.3f, 0.3f, 1.0f));
        m_Scene.CreateEntity(Geometry::Polygon{ { Math::Vec3(0.5f, -0.8f, 0.0f), Math::Vec3(1.5f, -0.8f, 0.0f), Math::Vec3(1.0f, 0.6f, 0.0f) } }, Math::Vec4(0.3f, 0.8f, 0.4f, 1.0f));
        m_Scene.CreateEntity(Geometry::Line{ Math::Vec3(-2.0f, -2.0f, 0.0f), Math::Vec3(2.0f, -2.0f, 0.0f) }, Math::Vec4(0.4f, 0.6f, 0.9f, 1.0f));
    }

    void SceneEditorExample::OnRender(Renderer::Renderer& renderer)
    {
        m_Scene.ForEachEntity([&renderer](const Scene::Entity& entity)
        {
            Geometry::Mesh mesh = Tessellation::Tessellator::Tessellate(entity.Geometry, {}, entity.Color);
            renderer.Draw(mesh);
        });
    }

    void SceneEditorExample::OnImGuiRender()
    {
        ImGui::Begin("Scene Editor");

        ImGui::Text("Entities: %zu", m_Scene.Count());
        ImGui::Separator();

        static float nextX = -2.5f;
        auto placeAndAdvance = [&]() { float x = nextX; nextX += 0.6f; if (nextX > 2.5f) nextX = -2.5f; return x; };

        if (ImGui::Button("Add Point"))
            m_Scene.CreateEntity(Geometry::Point{ Math::Vec3(placeAndAdvance(), 1.5f, 0.0f) }, Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
        ImGui::SameLine();
        if (ImGui::Button("Add Line"))
            m_Scene.CreateEntity(Geometry::Line{ Math::Vec3(placeAndAdvance(), 1.0f, 0.0f), Math::Vec3(placeAndAdvance(), 1.8f, 0.0f) }, Math::Vec4(0.4f, 0.6f, 0.9f, 1.0f));
        ImGui::SameLine();
        if (ImGui::Button("Add Circle"))
            m_Scene.CreateEntity(Geometry::Circle{ Math::Vec3(placeAndAdvance(), 0.0f, 0.0f), 0.5f }, Math::Vec4(0.9f, 0.3f, 0.3f, 1.0f));

        if (ImGui::Button("Add Arc"))
            m_Scene.CreateEntity(Geometry::Arc{ Math::Vec3(placeAndAdvance(), 0.0f, 0.0f), 0.5f, 0.0f, 3.14159265f }, Math::Vec4(0.9f, 0.7f, 0.2f, 1.0f));
        ImGui::SameLine();
        if (ImGui::Button("Add Polyline"))
        {
            float x = placeAndAdvance();
            m_Scene.CreateEntity(Geometry::Polyline{ { Math::Vec3(x, -1.0f, 0.0f), Math::Vec3(x + 0.4f, -0.5f, 0.0f), Math::Vec3(x + 0.8f, -1.0f, 0.0f) } }, Math::Vec4(0.7f, 0.4f, 0.9f, 1.0f));
        }
        ImGui::SameLine();
        if (ImGui::Button("Add Polygon"))
        {
            float x = placeAndAdvance();
            m_Scene.CreateEntity(Geometry::Polygon{ { Math::Vec3(x, -0.8f, 0.0f), Math::Vec3(x + 1.0f, -0.8f, 0.0f), Math::Vec3(x + 0.5f, 0.6f, 0.0f) } }, Math::Vec4(0.3f, 0.8f, 0.4f, 1.0f));
        }

        ImGui::Separator();

        std::vector<Scene::EntityID> toRemove;
        m_Scene.ForEachEntity([&](const Scene::Entity& entity)
        {
            ImGui::PushID(static_cast<int>(entity.Id.Index));
            ImGui::Text("%s", GeometryTypeName(entity.Geometry));
            ImGui::SameLine();
            if (ImGui::SmallButton("Remove"))
                toRemove.push_back(entity.Id);
            ImGui::PopID();
        });

        for (Scene::EntityID id : toRemove)
            m_Scene.DestroyEntity(id);

        ImGui::End();
    }
}
