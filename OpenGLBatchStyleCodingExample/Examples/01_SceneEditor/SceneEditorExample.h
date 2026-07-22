#pragma once

#include "Core/IExample.h"
#include "Scene/Scene.h"

namespace Examples
{
    // First real vertical slice: Scene -> Tessellator -> Renderer -> Batch
    // -> OpenGL, plus an ImGui panel to add/remove entities at runtime.
    class SceneEditorExample : public Engine::Core::IExample
    {
    public:
        void OnAttach() override;
        void OnRender(Engine::Renderer::Renderer& renderer) override;
        void OnImGuiRender() override;

    private:
        Engine::Scene::Scene m_Scene;
    };
}
