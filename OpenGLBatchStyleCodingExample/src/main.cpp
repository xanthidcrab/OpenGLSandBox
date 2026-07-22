#include "Core/Application.h"

#include "01_SceneEditor/SceneEditorExample.h"

#include <memory>

int main()
{
    Engine::Core::Application app(std::make_unique<Examples::SceneEditorExample>());
    app.Run();
    return 0;
}
