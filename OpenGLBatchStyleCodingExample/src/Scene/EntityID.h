#pragma once

#include <cstdint>
#include <functional>

namespace Engine::Scene
{
    // Generational index: Index identifies a slot, Generation guards
    // against a stale ID (from a destroyed entity) matching a new entity
    // that later reuses the same slot. This is what lets a future
    // Selection set or Undo/Redo command hold an EntityID safely across
    // entity add/remove without dangling.
    struct EntityID
    {
        static constexpr uint32_t InvalidIndex = 0xFFFFFFFFu;

        uint32_t Index = InvalidIndex;
        uint32_t Generation = 0;

        bool IsValid() const noexcept { return Index != InvalidIndex; }
        bool operator==(const EntityID&) const = default;
    };
}

namespace std
{
    template<>
    struct hash<Engine::Scene::EntityID>
    {
        size_t operator()(const Engine::Scene::EntityID& id) const noexcept
        {
            return (static_cast<size_t>(id.Index) << 32) ^ static_cast<size_t>(id.Generation);
        }
    };
}
