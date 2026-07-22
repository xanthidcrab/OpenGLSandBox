#include "Scene/Scene.h"

namespace Engine::Scene
{
    EntityID Scene::CreateEntity(Geometry::AnyGeometry geometry, const Math::Vec4& color)
    {
        uint32_t index;
        if (!m_FreeList.empty())
        {
            index = m_FreeList.back();
            m_FreeList.pop_back();
        }
        else
        {
            index = static_cast<uint32_t>(m_Slots.size());
            m_Slots.emplace_back();
        }

        Slot& slot = m_Slots[index];
        slot.Alive = true;

        EntityID id{ index, slot.Generation };
        slot.Data = Entity{ id, std::move(geometry), color, false };
        return id;
    }

    void Scene::DestroyEntity(EntityID id)
    {
        if (!IsValid(id))
            return;

        Slot& slot = m_Slots[id.Index];
        slot.Alive = false;
        slot.Generation++;
        m_FreeList.push_back(id.Index);
    }

    bool Scene::IsValid(EntityID id) const
    {
        if (!id.IsValid() || id.Index >= m_Slots.size())
            return false;

        const Slot& slot = m_Slots[id.Index];
        return slot.Alive && slot.Generation == id.Generation;
    }

    Entity* Scene::TryGetEntity(EntityID id)
    {
        return IsValid(id) ? &m_Slots[id.Index].Data : nullptr;
    }

    const Entity* Scene::TryGetEntity(EntityID id) const
    {
        return IsValid(id) ? &m_Slots[id.Index].Data : nullptr;
    }

    void Scene::ForEachEntity(const std::function<void(Entity&)>& fn)
    {
        for (Slot& slot : m_Slots)
        {
            if (slot.Alive)
                fn(slot.Data);
        }
    }

    void Scene::ForEachEntity(const std::function<void(const Entity&)>& fn) const
    {
        for (const Slot& slot : m_Slots)
        {
            if (slot.Alive)
                fn(slot.Data);
        }
    }

    size_t Scene::Count() const noexcept
    {
        size_t count = 0;
        for (const Slot& slot : m_Slots)
        {
            if (slot.Alive)
                ++count;
        }
        return count;
    }
}
