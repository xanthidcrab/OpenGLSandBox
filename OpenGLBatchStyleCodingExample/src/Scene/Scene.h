#pragma once

#include "Scene/Entity.h"

#include <functional>
#include <vector>

namespace Engine::Scene
{
    // Owns every Entity in the scene via a slot-map keyed by EntityID, so
    // Selection/Undo-Redo/Picking (not built yet) can hold an EntityID
    // across adds/removes without ever dangling.
    class Scene
    {
    public:
        EntityID CreateEntity(Geometry::AnyGeometry geometry, const Math::Vec4& color = Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
        void DestroyEntity(EntityID id);

        bool IsValid(EntityID id) const;
        Entity* TryGetEntity(EntityID id);
        const Entity* TryGetEntity(EntityID id) const;

        void ForEachEntity(const std::function<void(Entity&)>& fn);
        void ForEachEntity(const std::function<void(const Entity&)>& fn) const;

        size_t Count() const noexcept;

    private:
        struct Slot
        {
            Entity Data;
            uint32_t Generation = 0;
            bool Alive = false;
        };

        std::vector<Slot> m_Slots;
        std::vector<uint32_t> m_FreeList;
    };
}
