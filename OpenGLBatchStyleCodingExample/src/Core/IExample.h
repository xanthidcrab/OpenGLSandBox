#pragma once

namespace Engine::Renderer { class Renderer; }

namespace Engine::Core
{
    // One lesson/example per implementation. Methods default to no-ops
    // (not pure virtual) so a concrete Example only overrides what it
    // actually uses - most lessons won't need OnUpdate or OnDetach.
    class IExample
    {
    public:
        virtual ~IExample() = default;

        virtual void OnAttach() {}
        virtual void OnUpdate(float deltaTimeSeconds) { (void)deltaTimeSeconds; }
        virtual void OnRender(Renderer::Renderer& renderer) { (void)renderer; }
        virtual void OnImGuiRender() {}
        virtual void OnDetach() {}
    };
}
